# !/usr/bin/env python

import argparse
import logging
import time

from std_msgs.msg import Header
from geometry_msgs.msg import Point, Pose, PoseStamped, Quaternion
from nav_msgs.msg import Path
import numpy as np
import rosbag
import rospy
from scipy import ndimage
import yaml

from rospy_message_converter import message_converter


def extract_points_from_bag(bag_file, map_frame, camera_frame):
    """
    Read a rosbag and return transformation between given frames as a list of 2d points.
    """

    # Open ROS bag
    bag = rosbag.Bag(bag_file)

    # Initialize empty list for points from_bag
    points = []

    # Loop through messages in the "/tf" topic of the bag
    for _, msg, _ in bag.read_messages(topics=['/tf']):
        transform_stamped = msg.transforms[0]
        if transform_stamped.header.frame_id == map_frame and transform_stamped.child_frame_id == camera_frame:
            points.append([transform_stamped.transform.translation.x,
                           transform_stamped.transform.translation.y])

    # Close ROS bag
    logging.info("Read %s poses. Closing rosbag.", len(points))
    bag.close()

    return points


def filter_points(points, distance_factor, windows_size):
    """"
    From a list of points, remove points that are either identical to on of their neighbours
    or are considered outliers by comparing them to the median distance of all points.
    """

    # Convert point list to numpy type and separate x and y components into vectors
    point_matrix = np.array(points)
    x_vector = point_matrix[:, 0]
    y_vector = point_matrix[:, 1]

    # Compute distance between consecutive points
    distance_between_points = np.sqrt(
        np.diff(x_vector)**2 + np.diff(y_vector)**2)

    # Add some noise to distance measurements
    smoothed_distance_between_points = ndimage.gaussian_filter1d(
        distance_between_points, windows_size, mode='wrap')

    # Filter points where distance is either 0 or larger than the treshold
    maximum_distance = distance_factor * \
        np.median(smoothed_distance_between_points)
    x_vector_filtered = x_vector[:-1]
    y_vector_filtered = y_vector[:-1]
    x_vector_filtered = x_vector_filtered[(distance_between_points > 0) & (
        smoothed_distance_between_points < maximum_distance)]
    y_vector_filtered = y_vector_filtered[(distance_between_points > 0) & (
        smoothed_distance_between_points < maximum_distance)]

    # Convert back to list
    filter_points_list = np.column_stack(
        (x_vector_filtered, y_vector_filtered)).tolist()
    logging.info(
        "Filtered poses to remove outliers. %s poses left.", len(filter_points_list))

    return filter_points_list


def to_path(points, map_frame):
    """
    Transform a list of points into a nav_msgs/Path

    All time stamps will be from when this script was executed.
    """

    path = Path()
    stamp = rospy.Time.from_sec(time.time())
    header = Header(frame_id=map_frame, stamp=stamp)
    path.header = header
    identity_rotation = Quaternion(x=0, y=0, z=0, w=1)

    for point in points:
        point_msg = Point(x=point[0], y=point[1], z=0)
        pose_stamped_msg = PoseStamped(header=header, pose=Pose(
            position=point_msg, orientation=identity_rotation))
        path.poses.append(pose_stamped_msg)

    logging.info("Transformed poses to path message.")

    return path


def dump_yaml(message, out_file):
    """
    Dump a ros message into a yaml file that can be used by rostopic pub
    """

    # Convert message to dictionary
    dictionary = message_converter.convert_ros_message_to_dictionary(message)

    # Save path to YAML file
    with open(out_file, 'w') as file:
        yaml.dump(dictionary, file)
    logging.info("Wrote path to %s", out_file)


def parser():
    parser = argparse.ArgumentParser(
        "Read transformations from bag file, concatenate to path and dump to yaml file.")
    parser.add_argument("bag", type=str,
                        help="Path bag file containing tf information.")
    parser.add_argument("-c", "--camera-frame", type=str,
                        default="camera_top", help="Name of the camera frame id. Defaults to camera_top.")
    parser.add_argument("-m", "--map-frame", type=str,
                        default="stargazer", help="Name of the map frame id. Defaults to stargazer.")
    parser.add_argument("-o", "--out-file", type=str,
                        default="./path.yaml", help="Absolute path to output yaml file. Defaults to ./path.yaml")
    parser.add_argument(
        "-d",
        "--distance-factor",
        type=float,
        default=2,
        help="Points with a distance of more than distance-factor times the median distance of all points will be filtered. Defaults to 2")
    parser.add_argument(
        "-w",
        "--window-size",
        type=float,
        default=5,
        help="Size of floating window when smoothing before filtering points. Defaults to 5")

    return parser.parse_args()


if __name__ == '__main__':
    logging.basicConfig(format='%(levelname)s:%(message)s', level=logging.INFO)

    args = parser()
    points = extract_points_from_bag(
        args.bag, args.map_frame, args.camera_frame)
    filtered_points = filter_points(
        points, args.distance_factor, args.window_size)
    path = to_path(filtered_points, args.map_frame)
    dump_yaml(path, args.out_file)

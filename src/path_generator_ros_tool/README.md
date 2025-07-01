# PATH GENERATOR ROS TOOL
This package is used for generating and publishing a yaml file from a recorded path.

## Path generation

To generate a path, record a rosbag containing the `/tf` topic.
Next, execute `rosrun path_generator_ros_tool path_from_rosbag.py <path/to/bagfile>`. 
Use `--help` to see available options.
You will find the generated path at `./path.yaml` unless you have specified a different output file.

# Path publishing

Publish the path file either in the with the provided launch file or manually using `rostopic pub -l -f <path/to/path.yaml> </path/topic> nav_msgs/Path`.
The prior may come in handy when running this tool from a higher level launch file as you will have to define the path topic only once.
The launch file marked as standalone is meant for testing and development purposes and should not be included by a higher level launch file.

In the `res` directory of this package, you will find an exemplery rosbag and path file.

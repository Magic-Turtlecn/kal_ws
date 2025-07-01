#!/bin/sh

if [ -n "$DESTDIR" ] ; then
    case $DESTDIR in
        /*) # ok
            ;;
        *)
            /bin/echo "DESTDIR argument must be absolute... "
            /bin/echo "otherwise python's distutils will bork things."
            exit 1
    esac
fi

echo_and_run() { echo "+ $@" ; "$@" ; }

echo_and_run cd "/home/yzz/kal_ws/src/util_testing_ros"

# ensure that Python install destination exists
echo_and_run mkdir -p "$DESTDIR/home/yzz/kal_ws/install/lib/python3/dist-packages"

# Note that PYTHONPATH is pulled from the environment to support installing
# into one location when some dependencies were installed in another
# location, #123.
echo_and_run /usr/bin/env \
    PYTHONPATH="/home/yzz/kal_ws/install/lib/python3/dist-packages:/home/yzz/kal_ws/build/util_testing_ros/lib/python3/dist-packages:$PYTHONPATH" \
    CATKIN_BINARY_DIR="/home/yzz/kal_ws/build/util_testing_ros" \
    "/usr/bin/python3" \
    "/home/yzz/kal_ws/src/util_testing_ros/setup.py" \
    egg_info --egg-base /home/yzz/kal_ws/build/util_testing_ros \
    build --build-base "/home/yzz/kal_ws/build/util_testing_ros" \
    install \
    --root="${DESTDIR-/}" \
     --prefix="/home/yzz/kal_ws/install" --install-scripts="/home/yzz/kal_ws/install/bin"

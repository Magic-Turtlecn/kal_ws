## *********************************************************
##
## File autogenerated for the rosinterface_handler package
## by the dynamic_reconfigure package.
## Please do not edit.
##
## ********************************************************/

from dynamic_reconfigure.encoding import extract_params

inf = float('inf')

config_description = {'name': 'Default', 'type': '', 'state': True, 'cstate': 'true', 'id': 0, 'parent': 0, 'parameters': [{'name': 'verbosity_param_wo_default', 'type': 'str', 'default': '', 'level': 0, 'description': 'Sets the verbosity for this node', 'min': '', 'max': '', 'srcline': 292, 'srcfile': '/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py', 'edit_method': "{'enum': [{'name': 'debug', 'type': 'str', 'value': 'debug', 'srcline': 15, 'srcfile': '/home/yzz/kal_ws/devel/.private/rosinterface_handler/share/rosinterface_handler/cfg/DefaultsAtLaunch.cfg', 'description': '', 'ctype': 'std::string', 'cconsttype': 'const char * const'}, {'name': 'info', 'type': 'str', 'value': 'info', 'srcline': 16, 'srcfile': '/home/yzz/kal_ws/devel/.private/rosinterface_handler/share/rosinterface_handler/cfg/DefaultsAtLaunch.cfg', 'description': '', 'ctype': 'std::string', 'cconsttype': 'const char * const'}, {'name': 'warning', 'type': 'str', 'value': 'warning', 'srcline': 17, 'srcfile': '/home/yzz/kal_ws/devel/.private/rosinterface_handler/share/rosinterface_handler/cfg/DefaultsAtLaunch.cfg', 'description': '', 'ctype': 'std::string', 'cconsttype': 'const char * const'}, {'name': 'error', 'type': 'str', 'value': 'error', 'srcline': 18, 'srcfile': '/home/yzz/kal_ws/devel/.private/rosinterface_handler/share/rosinterface_handler/cfg/DefaultsAtLaunch.cfg', 'description': '', 'ctype': 'std::string', 'cconsttype': 'const char * const'}, {'name': 'fatal', 'type': 'str', 'value': 'fatal', 'srcline': 19, 'srcfile': '/home/yzz/kal_ws/devel/.private/rosinterface_handler/share/rosinterface_handler/cfg/DefaultsAtLaunch.cfg', 'description': '', 'ctype': 'std::string', 'cconsttype': 'const char * const'}], 'enum_description': 'Sets the verbosity for this node'}", 'ctype': 'std::string', 'cconsttype': 'const char * const'}, {'name': 'enum_int_param_wo_default', 'type': 'int', 'default': 0, 'level': 0, 'description': 'int enum', 'min': -2147483648, 'max': 2147483647, 'srcline': 292, 'srcfile': '/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py', 'edit_method': "{'enum': [{'name': 'Small', 'type': 'int', 'value': 0, 'srcline': 22, 'srcfile': '/home/yzz/kal_ws/devel/.private/rosinterface_handler/share/rosinterface_handler/cfg/DefaultsAtLaunch.cfg', 'description': '', 'ctype': 'int', 'cconsttype': 'const int'}, {'name': 'Medium', 'type': 'int', 'value': 1, 'srcline': 23, 'srcfile': '/home/yzz/kal_ws/devel/.private/rosinterface_handler/share/rosinterface_handler/cfg/DefaultsAtLaunch.cfg', 'description': '', 'ctype': 'int', 'cconsttype': 'const int'}, {'name': 'Large', 'type': 'int', 'value': 2, 'srcline': 24, 'srcfile': '/home/yzz/kal_ws/devel/.private/rosinterface_handler/share/rosinterface_handler/cfg/DefaultsAtLaunch.cfg', 'description': '', 'ctype': 'int', 'cconsttype': 'const int'}, {'name': 'ExtraLarge', 'type': 'int', 'value': 3, 'srcline': 25, 'srcfile': '/home/yzz/kal_ws/devel/.private/rosinterface_handler/share/rosinterface_handler/cfg/DefaultsAtLaunch.cfg', 'description': '', 'ctype': 'int', 'cconsttype': 'const int'}], 'enum_description': 'int enum'}", 'ctype': 'int', 'cconsttype': 'const int'}, {'name': 'enum_str_param_wo_default', 'type': 'str', 'default': '', 'level': 0, 'description': 'string enum', 'min': '', 'max': '', 'srcline': 292, 'srcfile': '/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py', 'edit_method': "{'enum': [{'name': 'Zero', 'type': 'str', 'value': 'Zero', 'srcline': 28, 'srcfile': '/home/yzz/kal_ws/devel/.private/rosinterface_handler/share/rosinterface_handler/cfg/DefaultsAtLaunch.cfg', 'description': '', 'ctype': 'std::string', 'cconsttype': 'const char * const'}, {'name': 'One', 'type': 'str', 'value': 'One', 'srcline': 29, 'srcfile': '/home/yzz/kal_ws/devel/.private/rosinterface_handler/share/rosinterface_handler/cfg/DefaultsAtLaunch.cfg', 'description': '', 'ctype': 'std::string', 'cconsttype': 'const char * const'}, {'name': 'Two', 'type': 'str', 'value': 'Two', 'srcline': 30, 'srcfile': '/home/yzz/kal_ws/devel/.private/rosinterface_handler/share/rosinterface_handler/cfg/DefaultsAtLaunch.cfg', 'description': '', 'ctype': 'std::string', 'cconsttype': 'const char * const'}, {'name': 'Three', 'type': 'str', 'value': 'Three', 'srcline': 31, 'srcfile': '/home/yzz/kal_ws/devel/.private/rosinterface_handler/share/rosinterface_handler/cfg/DefaultsAtLaunch.cfg', 'description': '', 'ctype': 'std::string', 'cconsttype': 'const char * const'}], 'enum_description': 'string enum'}", 'ctype': 'std::string', 'cconsttype': 'const char * const'}], 'groups': [], 'srcline': 247, 'srcfile': '/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py', 'class': 'DEFAULT', 'parentclass': '', 'parentname': 'Default', 'field': 'default', 'upper': 'DEFAULT', 'lower': 'groups'}

min = {}
max = {}
defaults = {}
level = {}
type = {}
all_level = 0

#def extract_params(config):
#    params = []
#    params.extend(config['parameters'])
#    for group in config['groups']:
#        params.extend(extract_params(group))
#    return params

for param in extract_params(config_description):
    min[param['name']] = param['min']
    max[param['name']] = param['max']
    defaults[param['name']] = param['default']
    level[param['name']] = param['level']
    type[param['name']] = param['type']
    all_level = all_level | param['level']

DefaultsAtLaunch_debug = 'debug'
DefaultsAtLaunch_info = 'info'
DefaultsAtLaunch_warning = 'warning'
DefaultsAtLaunch_error = 'error'
DefaultsAtLaunch_fatal = 'fatal'
DefaultsAtLaunch_Small = 0
DefaultsAtLaunch_Medium = 1
DefaultsAtLaunch_Large = 2
DefaultsAtLaunch_ExtraLarge = 3
DefaultsAtLaunch_Zero = 'Zero'
DefaultsAtLaunch_One = 'One'
DefaultsAtLaunch_Two = 'Two'
DefaultsAtLaunch_Three = 'Three'

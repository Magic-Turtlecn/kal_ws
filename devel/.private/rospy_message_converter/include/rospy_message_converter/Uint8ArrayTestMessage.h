// Generated by gencpp from file rospy_message_converter/Uint8ArrayTestMessage.msg
// DO NOT EDIT!


#ifndef ROSPY_MESSAGE_CONVERTER_MESSAGE_UINT8ARRAYTESTMESSAGE_H
#define ROSPY_MESSAGE_CONVERTER_MESSAGE_UINT8ARRAYTESTMESSAGE_H


#include <string>
#include <vector>
#include <memory>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace rospy_message_converter
{
template <class ContainerAllocator>
struct Uint8ArrayTestMessage_
{
  typedef Uint8ArrayTestMessage_<ContainerAllocator> Type;

  Uint8ArrayTestMessage_()
    : data()  {
    }
  Uint8ArrayTestMessage_(const ContainerAllocator& _alloc)
    : data(_alloc)  {
  (void)_alloc;
    }



   typedef std::vector<uint8_t, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<uint8_t>> _data_type;
  _data_type data;





  typedef boost::shared_ptr< ::rospy_message_converter::Uint8ArrayTestMessage_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::rospy_message_converter::Uint8ArrayTestMessage_<ContainerAllocator> const> ConstPtr;

}; // struct Uint8ArrayTestMessage_

typedef ::rospy_message_converter::Uint8ArrayTestMessage_<std::allocator<void> > Uint8ArrayTestMessage;

typedef boost::shared_ptr< ::rospy_message_converter::Uint8ArrayTestMessage > Uint8ArrayTestMessagePtr;
typedef boost::shared_ptr< ::rospy_message_converter::Uint8ArrayTestMessage const> Uint8ArrayTestMessageConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::rospy_message_converter::Uint8ArrayTestMessage_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::rospy_message_converter::Uint8ArrayTestMessage_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::rospy_message_converter::Uint8ArrayTestMessage_<ContainerAllocator1> & lhs, const ::rospy_message_converter::Uint8ArrayTestMessage_<ContainerAllocator2> & rhs)
{
  return lhs.data == rhs.data;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::rospy_message_converter::Uint8ArrayTestMessage_<ContainerAllocator1> & lhs, const ::rospy_message_converter::Uint8ArrayTestMessage_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace rospy_message_converter

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsMessage< ::rospy_message_converter::Uint8ArrayTestMessage_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::rospy_message_converter::Uint8ArrayTestMessage_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::rospy_message_converter::Uint8ArrayTestMessage_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::rospy_message_converter::Uint8ArrayTestMessage_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::rospy_message_converter::Uint8ArrayTestMessage_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::rospy_message_converter::Uint8ArrayTestMessage_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::rospy_message_converter::Uint8ArrayTestMessage_<ContainerAllocator> >
{
  static const char* value()
  {
    return "f43a8e1b362b75baa741461b46adc7e0";
  }

  static const char* value(const ::rospy_message_converter::Uint8ArrayTestMessage_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xf43a8e1b362b75baULL;
  static const uint64_t static_value2 = 0xa741461b46adc7e0ULL;
};

template<class ContainerAllocator>
struct DataType< ::rospy_message_converter::Uint8ArrayTestMessage_<ContainerAllocator> >
{
  static const char* value()
  {
    return "rospy_message_converter/Uint8ArrayTestMessage";
  }

  static const char* value(const ::rospy_message_converter::Uint8ArrayTestMessage_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::rospy_message_converter::Uint8ArrayTestMessage_<ContainerAllocator> >
{
  static const char* value()
  {
    return "# Size-agnostic uint8 array for testing purposes\n"
"uint8[] data\n"
;
  }

  static const char* value(const ::rospy_message_converter::Uint8ArrayTestMessage_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::rospy_message_converter::Uint8ArrayTestMessage_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.data);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct Uint8ArrayTestMessage_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::rospy_message_converter::Uint8ArrayTestMessage_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::rospy_message_converter::Uint8ArrayTestMessage_<ContainerAllocator>& v)
  {
    if (false || !indent.empty())
      s << std::endl;
    s << indent << "data: ";
    if (v.data.empty() || true)
      s << "[";
    for (size_t i = 0; i < v.data.size(); ++i)
    {
      if (true && i > 0)
        s << ", ";
      else if (!true)
        s << std::endl << indent << "  -";
      Printer<uint8_t>::stream(s, true ? std::string() : indent + "    ", v.data[i]);
    }
    if (v.data.empty() || true)
      s << "]";
  }
};

} // namespace message_operations
} // namespace ros

#endif // ROSPY_MESSAGE_CONVERTER_MESSAGE_UINT8ARRAYTESTMESSAGE_H

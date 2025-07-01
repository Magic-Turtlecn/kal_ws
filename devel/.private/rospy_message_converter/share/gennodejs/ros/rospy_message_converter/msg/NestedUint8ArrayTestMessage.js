// Auto-generated. Do not edit!

// (in-package rospy_message_converter.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let Uint8ArrayTestMessage = require('./Uint8ArrayTestMessage.js');

//-----------------------------------------------------------

class NestedUint8ArrayTestMessage {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.arrays = null;
    }
    else {
      if (initObj.hasOwnProperty('arrays')) {
        this.arrays = initObj.arrays
      }
      else {
        this.arrays = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type NestedUint8ArrayTestMessage
    // Serialize message field [arrays]
    // Serialize the length for message field [arrays]
    bufferOffset = _serializer.uint32(obj.arrays.length, buffer, bufferOffset);
    obj.arrays.forEach((val) => {
      bufferOffset = Uint8ArrayTestMessage.serialize(val, buffer, bufferOffset);
    });
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type NestedUint8ArrayTestMessage
    let len;
    let data = new NestedUint8ArrayTestMessage(null);
    // Deserialize message field [arrays]
    // Deserialize array length for message field [arrays]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.arrays = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.arrays[i] = Uint8ArrayTestMessage.deserialize(buffer, bufferOffset)
    }
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    object.arrays.forEach((val) => {
      length += Uint8ArrayTestMessage.getMessageSize(val);
    });
    return length + 4;
  }

  static datatype() {
    // Returns string type for a message object
    return 'rospy_message_converter/NestedUint8ArrayTestMessage';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '031a2ce5216a9e0c7998cc17696cf368';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    # array of arrays for testing purposes
    Uint8ArrayTestMessage[] arrays
    
    ================================================================================
    MSG: rospy_message_converter/Uint8ArrayTestMessage
    # Size-agnostic uint8 array for testing purposes
    uint8[] data
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new NestedUint8ArrayTestMessage(null);
    if (msg.arrays !== undefined) {
      resolved.arrays = new Array(msg.arrays.length);
      for (let i = 0; i < resolved.arrays.length; ++i) {
        resolved.arrays[i] = Uint8ArrayTestMessage.Resolve(msg.arrays[i]);
      }
    }
    else {
      resolved.arrays = []
    }

    return resolved;
    }
};

module.exports = NestedUint8ArrayTestMessage;

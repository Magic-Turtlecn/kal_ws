// Auto-generated. Do not edit!

// (in-package rospy_message_converter.srv)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let NestedUint8ArrayTestMessage = require('../msg/NestedUint8ArrayTestMessage.js');

//-----------------------------------------------------------


//-----------------------------------------------------------

class NestedUint8ArrayTestServiceRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.input = null;
    }
    else {
      if (initObj.hasOwnProperty('input')) {
        this.input = initObj.input
      }
      else {
        this.input = new NestedUint8ArrayTestMessage();
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type NestedUint8ArrayTestServiceRequest
    // Serialize message field [input]
    bufferOffset = NestedUint8ArrayTestMessage.serialize(obj.input, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type NestedUint8ArrayTestServiceRequest
    let len;
    let data = new NestedUint8ArrayTestServiceRequest(null);
    // Deserialize message field [input]
    data.input = NestedUint8ArrayTestMessage.deserialize(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += NestedUint8ArrayTestMessage.getMessageSize(object.input);
    return length;
  }

  static datatype() {
    // Returns string type for a service object
    return 'rospy_message_converter/NestedUint8ArrayTestServiceRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '287c5504f335b2f83a6aee90e3b61986';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    # service with nested types for testing purposes
    NestedUint8ArrayTestMessage input
    
    
    ================================================================================
    MSG: rospy_message_converter/NestedUint8ArrayTestMessage
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
    const resolved = new NestedUint8ArrayTestServiceRequest(null);
    if (msg.input !== undefined) {
      resolved.input = NestedUint8ArrayTestMessage.Resolve(msg.input)
    }
    else {
      resolved.input = new NestedUint8ArrayTestMessage()
    }

    return resolved;
    }
};

class NestedUint8ArrayTestServiceResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.output = null;
    }
    else {
      if (initObj.hasOwnProperty('output')) {
        this.output = initObj.output
      }
      else {
        this.output = new NestedUint8ArrayTestMessage();
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type NestedUint8ArrayTestServiceResponse
    // Serialize message field [output]
    bufferOffset = NestedUint8ArrayTestMessage.serialize(obj.output, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type NestedUint8ArrayTestServiceResponse
    let len;
    let data = new NestedUint8ArrayTestServiceResponse(null);
    // Deserialize message field [output]
    data.output = NestedUint8ArrayTestMessage.deserialize(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += NestedUint8ArrayTestMessage.getMessageSize(object.output);
    return length;
  }

  static datatype() {
    // Returns string type for a service object
    return 'rospy_message_converter/NestedUint8ArrayTestServiceResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '338d6242d9e71242debd0623f06ff2bd';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    
    NestedUint8ArrayTestMessage output
    
    
    ================================================================================
    MSG: rospy_message_converter/NestedUint8ArrayTestMessage
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
    const resolved = new NestedUint8ArrayTestServiceResponse(null);
    if (msg.output !== undefined) {
      resolved.output = NestedUint8ArrayTestMessage.Resolve(msg.output)
    }
    else {
      resolved.output = new NestedUint8ArrayTestMessage()
    }

    return resolved;
    }
};

module.exports = {
  Request: NestedUint8ArrayTestServiceRequest,
  Response: NestedUint8ArrayTestServiceResponse,
  md5sum() { return '5eb791b1c2426cb63f1fa2ab8df04df3'; },
  datatype() { return 'rospy_message_converter/NestedUint8ArrayTestService'; }
};

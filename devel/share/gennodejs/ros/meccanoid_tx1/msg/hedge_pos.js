// Auto-generated. Do not edit!

// (in-package meccanoid_tx1.msg)


"use strict";

let _serializer = require('../base_serialize.js');
let _deserializer = require('../base_deserialize.js');
let _finder = require('../find.js');

//-----------------------------------------------------------

class hedge_pos {
  constructor() {
    this.timestamp_ms = 0;
    this.x_m = 0.0;
    this.y_m = 0.0;
    this.z_m = 0.0;
    this.flags = 0;
  }

  static serialize(obj, bufferInfo) {
    // Serializes a message object of type hedge_pos
    // Serialize message field [timestamp_ms]
    bufferInfo = _serializer.int64(obj.timestamp_ms, bufferInfo);
    // Serialize message field [x_m]
    bufferInfo = _serializer.float64(obj.x_m, bufferInfo);
    // Serialize message field [y_m]
    bufferInfo = _serializer.float64(obj.y_m, bufferInfo);
    // Serialize message field [z_m]
    bufferInfo = _serializer.float64(obj.z_m, bufferInfo);
    // Serialize message field [flags]
    bufferInfo = _serializer.uint8(obj.flags, bufferInfo);
    return bufferInfo;
  }

  static deserialize(buffer) {
    //deserializes a message object of type hedge_pos
    let tmp;
    let len;
    let data = new hedge_pos();
    // Deserialize message field [timestamp_ms]
    tmp = _deserializer.int64(buffer);
    data.timestamp_ms = tmp.data;
    buffer = tmp.buffer;
    // Deserialize message field [x_m]
    tmp = _deserializer.float64(buffer);
    data.x_m = tmp.data;
    buffer = tmp.buffer;
    // Deserialize message field [y_m]
    tmp = _deserializer.float64(buffer);
    data.y_m = tmp.data;
    buffer = tmp.buffer;
    // Deserialize message field [z_m]
    tmp = _deserializer.float64(buffer);
    data.z_m = tmp.data;
    buffer = tmp.buffer;
    // Deserialize message field [flags]
    tmp = _deserializer.uint8(buffer);
    data.flags = tmp.data;
    buffer = tmp.buffer;
    return {
      data: data,
      buffer: buffer
    }
  }

  static datatype() {
    // Returns string type for a message object
    return 'meccanoid_tx1/hedge_pos';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '5d7dc3e9efe3ead353f74615346c8145';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    int64 timestamp_ms
    float64 x_m
    float64 y_m
    float64 z_m
    uint8 flags
    `;
  }

};

module.exports = hedge_pos;

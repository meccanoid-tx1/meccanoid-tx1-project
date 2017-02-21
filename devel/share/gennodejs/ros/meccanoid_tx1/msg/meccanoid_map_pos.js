// Auto-generated. Do not edit!

// (in-package meccanoid_tx1.msg)


"use strict";

let _serializer = require('../base_serialize.js');
let _deserializer = require('../base_deserialize.js');
let _finder = require('../find.js');

//-----------------------------------------------------------

class meccanoid_map_pos {
  constructor() {
    this.data = '';
  }

  static serialize(obj, bufferInfo) {
    // Serializes a message object of type meccanoid_map_pos
    // Serialize message field [data]
    bufferInfo = _serializer.string(obj.data, bufferInfo);
    return bufferInfo;
  }

  static deserialize(buffer) {
    //deserializes a message object of type meccanoid_map_pos
    let tmp;
    let len;
    let data = new meccanoid_map_pos();
    // Deserialize message field [data]
    tmp = _deserializer.string(buffer);
    data.data = tmp.data;
    buffer = tmp.buffer;
    return {
      data: data,
      buffer: buffer
    }
  }

  static datatype() {
    // Returns string type for a message object
    return 'meccanoid_tx1/meccanoid_map_pos';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '992ce8a1687cec8c8bd883ec73ca41d1';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    # -------------------------------#
    # Meccanoid map position message #
    # -------------------------------#
    
    # TODO: implement message fields
    
    string data
    `;
  }

};

module.exports = meccanoid_map_pos;

/*
 *  Copyright (c) 2016 The WebRTC project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#ifndef WEBRTC_MODULES_RTP_RTCP_SOURCE_RTCP_PACKET_SDES_H_
#define WEBRTC_MODULES_RTP_RTCP_SOURCE_RTCP_PACKET_SDES_H_

#include <string>
#include <vector>

#include "webrtc/base/basictypes.h"
#include "webrtc/base/constructormagic.h"
#include "webrtc/modules/rtp_rtcp/source/rtcp_packet.h"

namespace webrtc {
namespace rtcp {
class CommonHeader;
// Source Description (SDES) (RFC 3550).
class Sdes : public RtcpPacket {
 public:
  struct Chunk {
    uint32_t ssrc;
    std::string cname;
  };
  static const uint8_t kPacketType = 202;

  Sdes();
  ~Sdes() override;

  // Parse assumes header is already parsed and validated.
  bool Parse(const CommonHeader& packet);

  bool AddCName(uint32_t ssrc, std::string cname);

  const std::vector<Chunk>& chunks() const { return chunks_; }

  size_t BlockLength() const override { return block_length_; }

 protected:
  bool Create(uint8_t* packet,
              size_t* index,
              size_t max_length,
              RtcpPacket::PacketReadyCallback* callback) const override;

 private:
  static const size_t kMaxNumberOfChunks = 0x1f;

  std::vector<Chunk> chunks_;
  size_t block_length_;

  RTC_DISALLOW_COPY_AND_ASSIGN(Sdes);
};
}  // namespace rtcp
}  // namespace webrtc
#endif  // WEBRTC_MODULES_RTP_RTCP_SOURCE_RTCP_PACKET_SDES_H_
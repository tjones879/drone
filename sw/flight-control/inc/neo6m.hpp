#pragma once

#include <array>
#include <cstdint>

namespace neo {
enum class MsgClass : std::uint8_t
{
    NAV = 0x01,
    RXM = 0x02,
    INF = 0x04,
    ACK = 0x05,
    CFG = 0x06,
    MON = 0x0A,
    AID = 0x0B,
    TIM = 0x0D,
    ESF = 0x10
};

template<uint16_t len>
std::pair<std::uint8_t, std::uint8_t> constexpr checksum(
MsgClass cls,
uint8_t id,
const std::array<std::uint8_t, len> &vals)
{
    std::uint8_t a = static_cast<uint8_t>(cls);
    std::uint8_t b = a;

    a += id;
    b += a;

    a += len;
    b += a;

    for (auto v : vals) {
        a += v;
        b += a;
    }
    return { a, b };
}

template<uint16_t len>
class msg
{
public:
    constexpr msg(std::array<uint8_t, len> vals,
                  MsgClass cls,
                  uint8_t id,
                  const std::array<uint8_t, len> &data)
      : header({ 0xB5, 0x62 })
      , cls(cls)
      , id(id)
      , body(data)
      , check(cls, id, checksum(vals))
    {}

    constexpr std::array<uint8_t, len + 8> serialize()
    {
        auto ret = std::array<uint8_t, len + 8>{};
        ret[0] = header.first;
        ret[1] = header.second;
        ret[2] = static_cast<uint8_t>(cls);
        ret[3] = id;
        ret[4] = static_cast<uint8_t>(len >> 8);
        ret[5] = static_cast<uint8_t>(len & 0xFF);

        for (auto i = 0; i < body.size(); i++)
            ret[6 + i] = body[i];

        ret[len + 6] = check.first;
        ret[len + 7] = check.second;
        return ret;
    }
    std::pair<uint8_t, uint8_t> header;
    MsgClass cls;
    uint8_t id;
    std::array<uint8_t, len> body;
    std::pair<uint8_t, uint8_t> check;
};
} // namespace neo6m

class NEO6M
{};
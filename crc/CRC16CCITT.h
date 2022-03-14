//
// Created by Hintay on 2022/3/14.
//

#ifndef CTRANSPORT_CRC16CCITT_H
#define CTRANSPORT_CRC16CCITT_H

#include "Algorithm.hpp"

class CRC16CCITT: public CRCAlgorithm<CRC16CCITT, uint16_t, endian::big> {
public:
    explicit CRC16CCITT() { this->value_ = 0xFFFF; }

    using CRCAlgorithm::add;
    CRC16CCITT& add(const char *data, size_t length) override;

private:
    static const uint16_t crc_table_[256];
};


#endif //CTRANSPORT_CRC16CCITT_H

//
// Created by Hintay on 2022/3/14.
//

#ifndef CTRANSPORT_CRC64WE_H
#define CTRANSPORT_CRC64WE_H

#include "Algorithm.hpp"


class CRC64WE: public CRCAlgorithm<CRC64WE, uint64_t, endian::big> {
public:
    explicit CRC64WE() { this->value_ = 0xFFFFFFFFFFFFFFFF; }

    using CRCAlgorithm::add;
    CRC64WE& add(const char *data, size_t length) override;
    bool check_residue() override;
    explicit operator uint64_t() const override { return this->value_ ^ 0xFFFFFFFFFFFFFFFF; }
private:
    static const uint64_t crc_table_[256];
};


#endif //CTRANSPORT_CRC64WE_H

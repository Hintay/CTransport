//
// Created by Hintay on 2022/3/14.
//

#ifndef CTRANSPORT_CRC32C_H
#define CTRANSPORT_CRC32C_H

#include "Algorithm.hpp"

class CRC32C final : public CRCAlgorithm<CRC32C, uint32_t> {
public:
    explicit CRC32C() { this->value_ = 0xFFFFFFFF; }

    using CRCAlgorithm::add;
    CRC32C& add(const char *data, size_t length) override;
    bool check_residue() override;
    explicit operator uint32_t() const override { return this->value_ ^ 0xFFFFFFFF; }

private:
    static const uint32_t crc_table_[256];
};


#endif //CTRANSPORT_CRC32C_H

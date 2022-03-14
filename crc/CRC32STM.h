//
// Created by Hintay on 2022/3/11.
//

#ifndef CTRANSPORT_CRC32STM_H
#define CTRANSPORT_CRC32STM_H

#include "Algorithm.hpp"

class CRC32STM final : public CRCAlgorithm<CRC32STM, uint32_t> {
public:
    explicit CRC32STM() { this->value_ = 0xFFFFFFFF; }

    using CRCAlgorithm::add;
    CRC32STM& add(const char *data, size_t length) override;
    CRC32STM& add(uint32_t data);

private:
    static void add_dword(uint32_t *value, uint32_t data);
    static const uint32_t crc_table_[256];
};


#endif //CTRANSPORT_CRC32STM_H

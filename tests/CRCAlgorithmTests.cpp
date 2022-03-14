//
// Created by Hintay on 2022/3/13.
//

#include "gtest/gtest.h"
#include "CRC32STM.h"
#include "CRC32C.h"
#include "CRC16CCITT.h"
#include "CRC64WE.h"

TEST(CRC32STMTestSuite, String) { // NOLINT
    CRC32STM crc32;
    ASSERT_EQ(static_cast<uint32_t>(crc32), 0xFFFFFFFF);

    const auto value = static_cast<uint32_t>(crc32.add(std::string("123456789")));
    ASSERT_EQ(value, 0xAFF19057);
    ASSERT_EQ(crc32.value(), 0xAFF19057);
    ASSERT_EQ(static_cast<uint32_t>(crc32.add(static_cast<std::string>(crc32))), 0);
    ASSERT_EQ(crc32.value_as_string()[0], '\0');
    ASSERT_EQ(crc32.check_residue(), true);
}

TEST(CRC32STMTestSuite, VectorChar) { // NOLINT
    CRC32STM crc32;
    ASSERT_EQ(static_cast<uint32_t>(crc32), 0xFFFFFFFF);

    const auto test_string = "123456789";
    const auto value = static_cast<uint32_t>(crc32.add(std::vector<char>(test_string, test_string + strlen(test_string))));

    ASSERT_EQ(value, 0xAFF19057);
    ASSERT_EQ(static_cast<uint32_t>(crc32.add(static_cast<std::vector<char>>(crc32))), 0);
    ASSERT_EQ(crc32.value_as_vector()[0], '\0');
    ASSERT_EQ(crc32.check_residue(), true);
}

TEST(CRC32STMTestSuite, ValueCast) { // NOLINT
    CRC32STM crc32;
    ASSERT_EQ(crc32.value(), 0xFFFFFFFF);

    crc32.add(std::string("123456789"));
    ASSERT_EQ(crc32.value(), 0xAFF19057);
    ASSERT_EQ(static_cast<unsigned long>(crc32), 0xAFF19057);
    ASSERT_EQ(static_cast<uint64_t>(crc32), 0xAFF19057);
    ASSERT_EQ(static_cast<uint16_t>(crc32), 0x9057);
}

TEST(CRC32CTestSuite, String) { // NOLINT
    CRC32C crc32;
    ASSERT_EQ(static_cast<uint32_t>(crc32), 0);

    crc32.add(std::string{ "123456" });
    const auto value = static_cast<uint32_t>(crc32.add(std::string{ "789" }));

    ASSERT_EQ(value, 0xE3069283);
    ASSERT_EQ(static_cast<uint32_t>(crc32.add(static_cast<std::string>(crc32))), 0x48674BC7);  // Inverted residue
    ASSERT_EQ(crc32.check_residue(), true);
}

TEST(CRC16CCITTTestSuite, String) { // NOLINT
    CRC16CCITT crc16;
    ASSERT_EQ(static_cast<uint16_t>(crc16), 0xFFFF);

    crc16.add(std::string{ "123456" });
    const auto value = static_cast<uint16_t>(crc16.add(std::string{ "789" }));

    ASSERT_EQ(value, 0x29B1);
    ASSERT_EQ(static_cast<uint16_t>(crc16.add(static_cast<std::string>(crc16))), 0);
    ASSERT_EQ(crc16.check_residue(), true);
}

TEST(CRC64WETestSuite, String) { // NOLINT
    CRC64WE crc64;
    ASSERT_EQ(static_cast<uint64_t>(crc64), 0);

    crc64.add(std::string{ "123456" });
    const auto value = static_cast<uint64_t>(crc64.add(std::string{ "789" }));

    ASSERT_EQ(value, 0x62EC59E3F1A4F00A);
    ASSERT_EQ(static_cast<uint64_t>(crc64.add(static_cast<std::string>(crc64))), 0x3534142A6CE566D);
    ASSERT_EQ(crc64.check_residue(), true);
}

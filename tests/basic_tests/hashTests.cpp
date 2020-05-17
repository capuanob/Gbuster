//
// Created by bailey on 5/16/20.
//

// Test output of MD5 using RFC 1321 Examples
TEST(basic_check, test_eq) {
    EXPECT_EQ(md5::getDigest(""), "d41d8cd98f00b204e9800998ecf8427e");
    EXPECT_EQ(md5::getDigest("a"), "0cc175b9c0f1b6a831c399e269772661");
    EXPECT_EQ(md5::getDigest("abc"), "900150983cd24fb0d6963f7d28e17f72");
    EXPECT_EQ(md5::getDigest("message digest"), "f96b697d7cb7938d525a2f31aaf161d0");
    EXPECT_EQ(md5::getDigest("abcdefghijklmnopqrstuvwxyz"), "c3fcd3d76192e4007dfb496cca67e13b");
    EXPECT_EQ(md5::getDigest("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"), "d174ab98d277d9f5a5611c2c9f419d9f");
    EXPECT_EQ(md5::getDigest("12345678901234567890123456789012345678901234567890123456789012345678901234567890"), "57edf4a22be3c955ac49da2e2107b67a");
}
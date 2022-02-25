/**
 * @file ulog_hash.h
 * @brief heavily inspired by the pw_tokinizer hash functions
 * 
 * The LICENSE and SOURCE can be found in the externals/pw_tokinize folder
 * 
 */
#ifndef _ULOG_HASH_H_
#define _ULOG_HASH_H_

#include <stdint.h>
#include <stddef.h>
#include <assert.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief max string lenght ULOG_HASH will hash 
 * 
 */
#ifndef ULOG_HASH_STR_MAX_LEN
#define ULOG_HASH_STR_MAX_LEN 80
#endif

/**
 * @brief check if the lenght is smaller then max len
 * 
 * @param _len
 * @param _max_len
 * 
 * @return _len on succcess otherwise 0
 */
#define _CHECK_LEN(_len, _max_len) (_len < _max_len ? _len : 0)

/**
 * @brief Assert if the string is not compliant
 */
#ifndef ULOG_HASH_STR_ASSERT
    #define ULOG_HASH_STR_ASSERT(_str) static_assert(0 != _CHECK_LEN(sizeof(_str "") - 1, ULOG_HASH_STR_MAX_LEN), "format string is too long");
#endif
/**
 * @brief compile time impl. of ULOG_HASH_FUNCTION
 * 
 * @param _str string literal
 * @param _len lenght of string literal
 * 
 * @return const uint32_t
 */
#define ULOG_HASH_IMPL(_str, _len)                                \
    (const uint32_t)(_len +                                       \
            0x0001003fu * (uint8_t)(  0 < _len ? _str[  0] : 0) + \
            0x007e0f81u * (uint8_t)(  1 < _len ? _str[  1] : 0) + \
            0x2e86d0bfu * (uint8_t)(  2 < _len ? _str[  2] : 0) + \
            0x43ec5f01u * (uint8_t)(  3 < _len ? _str[  3] : 0) + \
            0x162c613fu * (uint8_t)(  4 < _len ? _str[  4] : 0) + \
            0xd62aee81u * (uint8_t)(  5 < _len ? _str[  5] : 0) + \
            0xa311b1bfu * (uint8_t)(  6 < _len ? _str[  6] : 0) + \
            0xd319be01u * (uint8_t)(  7 < _len ? _str[  7] : 0) + \
            0xb156c23fu * (uint8_t)(  8 < _len ? _str[  8] : 0) + \
            0x6698cd81u * (uint8_t)(  9 < _len ? _str[  9] : 0) + \
            0x0d1b92bfu * (uint8_t)( 10 < _len ? _str[ 10] : 0) + \
            0xcc881d01u * (uint8_t)( 11 < _len ? _str[ 11] : 0) + \
            0x7280233fu * (uint8_t)( 12 < _len ? _str[ 12] : 0) + \
            0x50c7ac81u * (uint8_t)( 13 < _len ? _str[ 13] : 0) + \
            0x8da473bfu * (uint8_t)( 14 < _len ? _str[ 14] : 0) + \
            0x4f377c01u * (uint8_t)( 15 < _len ? _str[ 15] : 0) + \
            0xfaa8843fu * (uint8_t)( 16 < _len ? _str[ 16] : 0) + \
            0x33b78b81u * (uint8_t)( 17 < _len ? _str[ 17] : 0) + \
            0x45ac54bfu * (uint8_t)( 18 < _len ? _str[ 18] : 0) + \
            0x7a27db01u * (uint8_t)( 19 < _len ? _str[ 19] : 0) + \
            0xeacfe53fu * (uint8_t)( 20 < _len ? _str[ 20] : 0) + \
            0xae686a81u * (uint8_t)( 21 < _len ? _str[ 21] : 0) + \
            0x563335bfu * (uint8_t)( 22 < _len ? _str[ 22] : 0) + \
            0x6c593a01u * (uint8_t)( 23 < _len ? _str[ 23] : 0) + \
            0xe3f6463fu * (uint8_t)( 24 < _len ? _str[ 24] : 0) + \
            0x5fda4981u * (uint8_t)( 25 < _len ? _str[ 25] : 0) + \
            0xe03916bfu * (uint8_t)( 26 < _len ? _str[ 26] : 0) + \
            0x44cb9901u * (uint8_t)( 27 < _len ? _str[ 27] : 0) + \
            0x871ba73fu * (uint8_t)( 28 < _len ? _str[ 28] : 0) + \
            0xe70d2881u * (uint8_t)( 29 < _len ? _str[ 29] : 0) + \
            0x04bdf7bfu * (uint8_t)( 30 < _len ? _str[ 30] : 0) + \
            0x227ef801u * (uint8_t)( 31 < _len ? _str[ 31] : 0) + \
            0x7540083fu * (uint8_t)( 32 < _len ? _str[ 32] : 0) + \
            0xe3010781u * (uint8_t)( 33 < _len ? _str[ 33] : 0) + \
            0xe4c1d8bfu * (uint8_t)( 34 < _len ? _str[ 34] : 0) + \
            0x24735701u * (uint8_t)( 35 < _len ? _str[ 35] : 0) + \
            0x4f63693fu * (uint8_t)( 36 < _len ? _str[ 36] : 0) + \
            0xf2b5e681u * (uint8_t)( 37 < _len ? _str[ 37] : 0) + \
            0xa144b9bfu * (uint8_t)( 38 < _len ? _str[ 38] : 0) + \
            0x69a8b601u * (uint8_t)( 39 < _len ? _str[ 39] : 0) + \
            0xb685ca3fu * (uint8_t)( 40 < _len ? _str[ 40] : 0) + \
            0xb52bc581u * (uint8_t)( 41 < _len ? _str[ 41] : 0) + \
            0x5b469abfu * (uint8_t)( 42 < _len ? _str[ 42] : 0) + \
            0x111f1501u * (uint8_t)( 43 < _len ? _str[ 43] : 0) + \
            0x4ba72b3fu * (uint8_t)( 44 < _len ? _str[ 44] : 0) + \
            0xc962a481u * (uint8_t)( 45 < _len ? _str[ 45] : 0) + \
            0x33c77bbfu * (uint8_t)( 46 < _len ? _str[ 46] : 0) + \
            0x39d67401u * (uint8_t)( 47 < _len ? _str[ 47] : 0) + \
            0xafc78c3fu * (uint8_t)( 48 < _len ? _str[ 48] : 0) + \
            0xce5a8381u * (uint8_t)( 49 < _len ? _str[ 49] : 0) + \
            0x4bc75cbfu * (uint8_t)( 50 < _len ? _str[ 50] : 0) + \
            0x02ced301u * (uint8_t)( 51 < _len ? _str[ 51] : 0) + \
            0x83e6ed3fu * (uint8_t)( 52 < _len ? _str[ 52] : 0) + \
            0x63136281u * (uint8_t)( 53 < _len ? _str[ 53] : 0) + \
            0xc4463dbfu * (uint8_t)( 54 < _len ? _str[ 54] : 0) + \
            0x8b083201u * (uint8_t)( 55 < _len ? _str[ 55] : 0) + \
            0x69054e3fu * (uint8_t)( 56 < _len ? _str[ 56] : 0) + \
            0x268d4181u * (uint8_t)( 57 < _len ? _str[ 57] : 0) + \
            0xbe441ebfu * (uint8_t)( 58 < _len ? _str[ 58] : 0) + \
            0xf1829101u * (uint8_t)( 59 < _len ? _str[ 59] : 0) + \
            0x0022af3fu * (uint8_t)( 60 < _len ? _str[ 60] : 0) + \
            0xb7c82081u * (uint8_t)( 61 < _len ? _str[ 61] : 0) + \
            0x5ac0ffbfu * (uint8_t)( 62 < _len ? _str[ 62] : 0) + \
            0x553df001u * (uint8_t)( 63 < _len ? _str[ 63] : 0) + \
            0xea3f103fu * (uint8_t)( 64 < _len ? _str[ 64] : 0) + \
            0xb5c3ff81u * (uint8_t)( 65 < _len ? _str[ 65] : 0) + \
            0xbabce0bfu * (uint8_t)( 66 < _len ? _str[ 66] : 0) + \
            0xd53a4f01u * (uint8_t)( 67 < _len ? _str[ 67] : 0) + \
            0xc85a713fu * (uint8_t)( 68 < _len ? _str[ 68] : 0) + \
            0xbf80de81u * (uint8_t)( 69 < _len ? _str[ 69] : 0) + \
            0xff37c1bfu * (uint8_t)( 70 < _len ? _str[ 70] : 0) + \
            0x9077ae01u * (uint8_t)( 71 < _len ? _str[ 71] : 0) + \
            0x3b74d23fu * (uint8_t)( 72 < _len ? _str[ 72] : 0) + \
            0x73febd81u * (uint8_t)( 73 < _len ? _str[ 73] : 0) + \
            0x4931a2bfu * (uint8_t)( 74 < _len ? _str[ 74] : 0) + \
            0xa5f60d01u * (uint8_t)( 75 < _len ? _str[ 75] : 0) + \
            0xe48e333fu * (uint8_t)( 76 < _len ? _str[ 76] : 0) + \
            0x723d9c81u * (uint8_t)( 77 < _len ? _str[ 77] : 0) + \
            0xb9aa83bfu * (uint8_t)( 78 < _len ? _str[ 78] : 0) + \
            0x34b56c01u * (uint8_t)( 79 < _len ? _str[ 79] : 0) + \
            0x64a6943fu * (uint8_t)( 80 < _len ? _str[ 80] : 0) + \
            0x593d7b81u * (uint8_t)( 81 < _len ? _str[ 81] : 0) + \
            0x71a264bfu * (uint8_t)( 82 < _len ? _str[ 82] : 0) + \
            0x5bb5cb01u * (uint8_t)( 83 < _len ? _str[ 83] : 0) + \
            0x5cbdf53fu * (uint8_t)( 84 < _len ? _str[ 84] : 0) + \
            0xc7fe5a81u * (uint8_t)( 85 < _len ? _str[ 85] : 0) + \
            0x921945bfu * (uint8_t)( 86 < _len ? _str[ 86] : 0) + \
            0x39f72a01u * (uint8_t)( 87 < _len ? _str[ 87] : 0) + \
            0x6dd4563fu * (uint8_t)( 88 < _len ? _str[ 88] : 0) + \
            0x5d803981u * (uint8_t)( 89 < _len ? _str[ 89] : 0) + \
            0x3c0f26bfu * (uint8_t)( 90 < _len ? _str[ 90] : 0) + \
            0xee798901u * (uint8_t)( 91 < _len ? _str[ 91] : 0) + \
            0x38e9b73fu * (uint8_t)( 92 < _len ? _str[ 92] : 0) + \
            0xb8c31881u * (uint8_t)( 93 < _len ? _str[ 93] : 0) + \
            0x908407bfu * (uint8_t)( 94 < _len ? _str[ 94] : 0) + \
            0x983ce801u * (uint8_t)( 95 < _len ? _str[ 95] : 0) + \
            0x5efe183fu * (uint8_t)( 96 < _len ? _str[ 96] : 0) + \
            0x78c6f781u * (uint8_t)( 97 < _len ? _str[ 97] : 0) + \
            0xb077e8bfu * (uint8_t)( 98 < _len ? _str[ 98] : 0) + \
            0x56414701u * (uint8_t)( 99 < _len ? _str[ 99] : 0) + \
            0x8111793fu * (uint8_t)(100 < _len ? _str[100] : 0) + \
            0x3c8bd681u * (uint8_t)(101 < _len ? _str[101] : 0) + \
            0xbceac9bfu * (uint8_t)(102 < _len ? _str[102] : 0) + \
            0x4786a601u * (uint8_t)(103 < _len ? _str[103] : 0) + \
            0x4023da3fu * (uint8_t)(104 < _len ? _str[104] : 0) + \
            0xa311b581u * (uint8_t)(105 < _len ? _str[105] : 0) + \
            0xd6dcaabfu * (uint8_t)(106 < _len ? _str[106] : 0) + \
            0x8b0d0501u * (uint8_t)(107 < _len ? _str[107] : 0) + \
            0x3d353b3fu * (uint8_t)(108 < _len ? _str[108] : 0) + \
            0x4b589481u * (uint8_t)(109 < _len ? _str[109] : 0) + \
            0x1f4d8bbfu * (uint8_t)(110 < _len ? _str[110] : 0) + \
            0x3fd46401u * (uint8_t)(111 < _len ? _str[111] : 0) + \
            0x19459c3fu * (uint8_t)(112 < _len ? _str[112] : 0) + \
            0xd4607381u * (uint8_t)(113 < _len ? _str[113] : 0) + \
            0xb73d6cbfu * (uint8_t)(114 < _len ? _str[114] : 0) + \
            0x84dcc301u * (uint8_t)(115 < _len ? _str[115] : 0) + \
            0x7554fd3fu * (uint8_t)(116 < _len ? _str[116] : 0) + \
            0xdd295281u * (uint8_t)(117 < _len ? _str[117] : 0) + \
            0xbfac4dbfu * (uint8_t)(118 < _len ? _str[118] : 0) + \
            0x79262201u * (uint8_t)(119 < _len ? _str[119] : 0) + \
            0xf2635e3fu * (uint8_t)(120 < _len ? _str[120] : 0) + \
            0x04b33181u * (uint8_t)(121 < _len ? _str[121] : 0) + \
            0x599a2ebfu * (uint8_t)(122 < _len ? _str[122] : 0) + \
            0x3bb08101u * (uint8_t)(123 < _len ? _str[123] : 0) + \
            0x3170bf3fu * (uint8_t)(124 < _len ? _str[124] : 0) + \
            0xe9fe1081u * (uint8_t)(125 < _len ? _str[125] : 0) + \
            0xa6070fbfu * (uint8_t)(126 < _len ? _str[126] : 0) + \
            0xeb7be001u * (uint8_t)(127 < _len ? _str[127] : 0) + \
            0xd37d203fu * (uint8_t)(128 < _len ? _str[128] : 0) + \
            0x2c09ef81u * (uint8_t)(129 < _len ? _str[129] : 0) + \
            0xc5f2f0bfu * (uint8_t)(130 < _len ? _str[130] : 0) + \
            0xa7883f01u * (uint8_t)(131 < _len ? _str[131] : 0) + \
            0x7988813fu * (uint8_t)(132 < _len ? _str[132] : 0) + \
            0x69d6ce81u * (uint8_t)(133 < _len ? _str[133] : 0) + \
            0xda5dd1bfu * (uint8_t)(134 < _len ? _str[134] : 0) + \
            0x8ed59e01u * (uint8_t)(135 < _len ? _str[135] : 0) + \
            0xc492e23fu * (uint8_t)(136 < _len ? _str[136] : 0) + \
            0x4264ad81u * (uint8_t)(137 < _len ? _str[137] : 0) + \
            0x0447b2bfu * (uint8_t)(138 < _len ? _str[138] : 0) + \
            0xc063fd01u * (uint8_t)(139 < _len ? _str[139] : 0) + \
            0x559c433fu * (uint8_t)(140 < _len ? _str[140] : 0) + \
            0x54b38c81u * (uint8_t)(141 < _len ? _str[141] : 0) + \
            0x64b093bfu * (uint8_t)(142 < _len ? _str[142] : 0) + \
            0x5b335c01u * (uint8_t)(143 < _len ? _str[143] : 0) + \
            0xcda4a43fu * (uint8_t)(144 < _len ? _str[144] : 0) + \
            0x3fc36b81u * (uint8_t)(145 < _len ? _str[145] : 0) + \
            0x1c9874bfu * (uint8_t)(146 < _len ? _str[146] : 0) + \
            0x7e43bb01u * (uint8_t)(147 < _len ? _str[147] : 0) + \
            0xcdac053fu * (uint8_t)(148 < _len ? _str[148] : 0) + \
            0xa2944a81u * (uint8_t)(149 < _len ? _str[149] : 0) + \
            0x4cff55bfu * (uint8_t)(150 < _len ? _str[150] : 0) + \
            0x48951a01u * (uint8_t)(151 < _len ? _str[151] : 0) + \
            0xf6b2663fu * (uint8_t)(152 < _len ? _str[152] : 0) + \
            0x1c262981u * (uint8_t)(153 < _len ? _str[153] : 0) + \
            0x16e536bfu * (uint8_t)(154 < _len ? _str[154] : 0) + \
            0xd9277901u * (uint8_t)(155 < _len ? _str[155] : 0) + \
            0xe9b7c73fu * (uint8_t)(156 < _len ? _str[156] : 0) + \
            0x4b790881u * (uint8_t)(157 < _len ? _str[157] : 0) + \
            0x9b4a17bfu * (uint8_t)(158 < _len ? _str[158] : 0) + \
            0x4efad801u * (uint8_t)(159 < _len ? _str[159] : 0) + \
            0x47bc283fu * (uint8_t)(160 < _len ? _str[160] : 0) + \
            0xcf8ce781u * (uint8_t)(161 < _len ? _str[161] : 0) + \
            0xfb2df8bfu * (uint8_t)(162 < _len ? _str[162] : 0) + \
            0xc90f3701u * (uint8_t)(163 < _len ? _str[163] : 0) + \
            0xb1bf893fu * (uint8_t)(164 < _len ? _str[164] : 0) + \
            0x4761c681u * (uint8_t)(165 < _len ? _str[165] : 0) + \
            0x5790d9bfu * (uint8_t)(166 < _len ? _str[166] : 0) + \
            0x66649601u * (uint8_t)(167 < _len ? _str[167] : 0) + \
            0xc8c1ea3fu * (uint8_t)(168 < _len ? _str[168] : 0) + \
            0x51f7a581u * (uint8_t)(169 < _len ? _str[169] : 0) + \
            0xd172babfu * (uint8_t)(170 < _len ? _str[170] : 0) + \
            0x45faf501u * (uint8_t)(171 < _len ? _str[171] : 0) + \
            0x2dc34b3fu * (uint8_t)(172 < _len ? _str[172] : 0) + \
            0x8e4e8481u * (uint8_t)(173 < _len ? _str[173] : 0) + \
            0x89d39bbfu * (uint8_t)(174 < _len ? _str[174] : 0) + \
            0x86d25401u * (uint8_t)(175 < _len ? _str[175] : 0) + \
            0x81c3ac3fu * (uint8_t)(176 < _len ? _str[176] : 0) + \
            0x9b666381u * (uint8_t)(177 < _len ? _str[177] : 0) + \
            0xa1b37cbfu * (uint8_t)(178 < _len ? _str[178] : 0) + \
            0x47eab301u * (uint8_t)(179 < _len ? _str[179] : 0) + \
            0x65c30d3fu * (uint8_t)(180 < _len ? _str[180] : 0) + \
            0x183f4281u * (uint8_t)(181 < _len ? _str[181] : 0) + \
            0x3a125dbfu * (uint8_t)(182 < _len ? _str[182] : 0) + \
            0xa8441201u * (uint8_t)(183 < _len ? _str[183] : 0) + \
            0x7ac16e3fu * (uint8_t)(184 < _len ? _str[184] : 0) + \
            0xa3d92181u * (uint8_t)(185 < _len ? _str[185] : 0) + \
            0x73f03ebfu * (uint8_t)(186 < _len ? _str[186] : 0) + \
            0xc6de7101u * (uint8_t)(187 < _len ? _str[187] : 0) + \
            0x61becf3fu * (uint8_t)(188 < _len ? _str[188] : 0) + \
            0xdd340081u * (uint8_t)(189 < _len ? _str[189] : 0) + \
            0x704d1fbfu * (uint8_t)(190 < _len ? _str[190] : 0) + \
            0xc2b9d001u * (uint8_t)(191 < _len ? _str[191] : 0) + \
            0xbbbb303fu * (uint8_t)(192 < _len ? _str[192] : 0) + \
            0x634fdf81u * (uint8_t)(193 < _len ? _str[193] : 0) + \
            0x502900bfu * (uint8_t)(194 < _len ? _str[194] : 0) + \
            0xbad62f01u * (uint8_t)(195 < _len ? _str[195] : 0) + \
            0x29b6913fu * (uint8_t)(196 < _len ? _str[196] : 0) + \
            0xd52cbe81u * (uint8_t)(197 < _len ? _str[197] : 0) + \
            0x3483e1bfu * (uint8_t)(198 < _len ? _str[198] : 0) + \
            0xce338e01u * (uint8_t)(199 < _len ? _str[199] : 0) + \
            0x4cb0f23fu * (uint8_t)(200 < _len ? _str[200] : 0) + \
            0xd1ca9d81u * (uint8_t)(201 < _len ? _str[201] : 0) + \
            0x3e5dc2bfu * (uint8_t)(202 < _len ? _str[202] : 0) + \
            0x1bd1ed01u * (uint8_t)(203 < _len ? _str[203] : 0) + \
            0xc5aa533fu * (uint8_t)(204 < _len ? _str[204] : 0) + \
            0xf8297c81u * (uint8_t)(205 < _len ? _str[205] : 0) + \
            0x8eb6a3bfu * (uint8_t)(206 < _len ? _str[206] : 0) + \
            0xc2b14c01u * (uint8_t)(207 < _len ? _str[207] : 0) + \
            0x35a2b43fu * (uint8_t)(208 < _len ? _str[208] : 0) + \
            0xe7495b81u * (uint8_t)(209 < _len ? _str[209] : 0) + \
            0x468e84bfu * (uint8_t)(210 < _len ? _str[210] : 0) + \
            0xe1d1ab01u * (uint8_t)(211 < _len ? _str[211] : 0) + \
            0x3d9a153fu * (uint8_t)(212 < _len ? _str[212] : 0) + \
            0x3e2a3a81u * (uint8_t)(213 < _len ? _str[213] : 0) + \
            0x86e565bfu * (uint8_t)(214 < _len ? _str[214] : 0) + \
            0x98330a01u * (uint8_t)(215 < _len ? _str[215] : 0) + \
            0x7e90763fu * (uint8_t)(216 < _len ? _str[216] : 0) + \
            0x9bcc1981u * (uint8_t)(217 < _len ? _str[217] : 0) + \
            0x70bb46bfu * (uint8_t)(218 < _len ? _str[218] : 0) + \
            0x04d56901u * (uint8_t)(219 < _len ? _str[219] : 0) + \
            0x9985d73fu * (uint8_t)(220 < _len ? _str[220] : 0) + \
            0x9f2ef881u * (uint8_t)(221 < _len ? _str[221] : 0) + \
            0x251027bfu * (uint8_t)(222 < _len ? _str[222] : 0) + \
            0x46b8c801u * (uint8_t)(223 < _len ? _str[223] : 0) + \
            0x2f7a383fu * (uint8_t)(224 < _len ? _str[224] : 0) + \
            0xe752d781u * (uint8_t)(225 < _len ? _str[225] : 0) + \
            0xc4e408bfu * (uint8_t)(226 < _len ? _str[226] : 0) + \
            0x7cdd2701u * (uint8_t)(227 < _len ? _str[227] : 0) + \
            0xe16d993fu * (uint8_t)(228 < _len ? _str[228] : 0) + \
            0x1337b681u * (uint8_t)(229 < _len ? _str[229] : 0) + \
            0x7136e9bfu * (uint8_t)(230 < _len ? _str[230] : 0) + \
            0xc6428601u * (uint8_t)(231 < _len ? _str[231] : 0) + \
            0x505ffa3fu * (uint8_t)(232 < _len ? _str[232] : 0) + \
            0xc1dd9581u * (uint8_t)(233 < _len ? _str[233] : 0) + \
            0x4b08cabfu * (uint8_t)(234 < _len ? _str[234] : 0) + \
            0x41e8e501u * (uint8_t)(235 < _len ? _str[235] : 0) + \
            0x1d515b3fu * (uint8_t)(236 < _len ? _str[236] : 0) + \
            0x92447481u * (uint8_t)(237 < _len ? _str[237] : 0) + \
            0x7359abbfu * (uint8_t)(238 < _len ? _str[238] : 0) + \
            0x0ed04401u * (uint8_t)(239 < _len ? _str[239] : 0) + \
            0xe941bc3fu * (uint8_t)(240 < _len ? _str[240] : 0) + \
            0x236c5381u * (uint8_t)(241 < _len ? _str[241] : 0) + \
            0x0b298cbfu * (uint8_t)(242 < _len ? _str[242] : 0) + \
            0x4bf8a301u * (uint8_t)(243 < _len ? _str[243] : 0) + \
            0x55311d3fu * (uint8_t)(244 < _len ? _str[244] : 0) + \
            0x14553281u * (uint8_t)(245 < _len ? _str[245] : 0) + \
            0x33786dbfu * (uint8_t)(246 < _len ? _str[246] : 0) + \
            0x18620201u * (uint8_t)(247 < _len ? _str[247] : 0) + \
            0x021f7e3fu * (uint8_t)(248 < _len ? _str[248] : 0) + \
            0x03ff1181u * (uint8_t)(249 < _len ? _str[249] : 0) + \
            0x0d464ebfu * (uint8_t)(250 < _len ? _str[250] : 0) + \
            0x930c6101u * (uint8_t)(251 < _len ? _str[251] : 0) + \
            0x910cdf3fu * (uint8_t)(252 < _len ? _str[252] : 0) + \
            0x9169f081u * (uint8_t)(253 < _len ? _str[253] : 0) + \
            0xb9932fbfu * (uint8_t)(254 < _len ? _str[254] : 0) + \
            0xdaf7c001u * (uint8_t)(255 < _len ? _str[255] : 0))

/**
 * @brief calculate hash of a string literal
 * 
 * @param _str must be a strin literal
 * 
 */
#define ULOG_HASH(_str) ULOG_HASH_IMPL(_str, _CHECK_LEN(sizeof(_str "") - 1, ULOG_HASH_STR_MAX_LEN))

/**
 * @brief calculate hash of a string at run time
 * 
 * @param str string
 * @param len string lenght
 * @return uint32_t string hash
 */
static inline uint32_t ulog_hash(char const* str, size_t len)
{

    uint32_t hash = len;
    const uint32_t seed = 65599;
    uint32_t coefficient = seed;

    for (size_t i = 0; i < len; ++i)
    {
        hash += coefficient * (uint8_t)str[i];
        coefficient *= seed;
    }
    return hash;
}

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif

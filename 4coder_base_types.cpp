/*
 * 4coder base types
 */

// TOP

#if !defined(FCODER_BASE_TYPES_CPP)
#define FCODER_BASE_TYPES_CPP

#define C_MATH 1

static i32
ceil32(f32 v){
    return(((v)>0)?( (v == (i32)(v))?((i32)(v)):((i32)((v)+1.f)) ):( ((i32)(v)) ));
}

static i32
floor32(f32 v){
    return(((v)<0)?( (v == (i32)(v))?((i32)(v)):((i32)((v)-1.f)) ):( ((i32)(v)) ));
}

static i32
round32(f32 v){
    return(floor32(v + 0.5f));
}

static i8
round_up_i8(i8 x, i8 b){
    x += b - 1;
    x -= x%b;
    return(x);
}
static u8
round_up_u8(u8 x, u8 b){
    x += b - 1;
    x -= x%b;
    return(x);
}
static i16
round_up_i16(i16 x, i16 b){
    x += b - 1;
    x -= x%b;
    return(x);
}
static u16
round_up_u16(u16 x, u16 b){
    x += b - 1;
    x -= x%b;
    return(x);
}
static i32
round_up_i32(i32 x, i32 b){
    x += b - 1;
    x -= x%b;
    return(x);
}
static u32
round_up_u32(u32 x, u32 b){
    x += b - 1;
    x -= x%b;
    return(x);
}
static i64
round_up_i64(i64 x, i64 b){
    x += b - 1;
    x -= x%b;
    return(x);
}
static u64
round_up_u64(u64 x, u64 b){
    x += b - 1;
    x -= x%b;
    return(x);
}
static imem
round_up_imem(imem x, imem b){
    x += b - 1;
    x -= x%b;
    return(x);
}
static umem
round_up_umem(umem x, umem b){
    x += b - 1;
    x -= x%b;
    return(x);
}

static i8
round_down_i8(i8 x, i8 b){
    x -= x%b;
    return(x);
}
static u8
round_down_u8(u8 x, u8 b){
    x -= x%b;
    return(x);
}
static i16
round_down_i16(i16 x, i16 b){
    x -= x%b;
    return(x);
}
static u16
round_down_u16(u16 x, u16 b){
    x -= x%b;
    return(x);
}
static i32
round_down_i32(i32 x, i32 b){
    x -= x%b;
    return(x);
}
static u32
round_down_u32(u32 x, u32 b){
    x -= x%b;
    return(x);
}
static i64
round_down_i64(i64 x, i64 b){
    x -= x%b;
    return(x);
}
static u64
round_down_u64(u64 x, u64 b){
    x -= x%b;
    return(x);
}
static imem
round_down_imem(imem x, imem b){
    x -= x%b;
    return(x);
}
static umem
round_down_umem(umem x, umem b){
    x -= x%b;
    return(x);
}

static f32
f32_integer(f32 x){
    return((f32)((i32)x));
}

static u32
round_up_pot_u32(u32 x){
    --x;
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
    ++x;
    return(x);
}

////////////////////////////////

static Data
make_data(void *memory, umem size){
    Data data = {(u8*)memory, size};
    return(data);
}

global_const Data zero_data = {};

#define data_initr(m,s) {(m), (s)}
#define data_initr_struct(s) {(s), sizeof(*(s))}
#define data_initr_array(a) {(a), sizeof(a)}
#define data_initr_string(s) {(s), sizeof(s) - 1}

////////////////////////////////

static void
block_zero(void *mem, umem size){
    for (u8 *p = (u8*)mem, *e = p + size; p < e; p += 1){
        *p = 0;
    }
}
static void
block_fill_ones(void *mem, umem size){
    for (u8 *p = (u8*)mem, *e = p + size; p < e; p += 1){
        *p = 0xFF;
    }
}
static void
block_copy(void *dst, void *src, umem size){
    u8 *d = (u8*)dst;
    u8 *s = (u8*)src;
    if (d < s){
        u8 *e = d + size;
        for (; d < e; d += 1, s += 1){
            *d = *s;
        }
    }
    else if (d > s){
        u8 *e = d;
        d += size - 1;
        s += size - 1;
        for (; d >= e; d -= 1, s -= 1){
            *d = *s;
        }
    }
}
static b32
block_match(void *a, void *b, umem size){
    b32 result = true;
    for (u8 *pa = (u8*)a, *pb = (u8*)b, *ea = pa + size; pa < ea; pa += 1, pb += 1){
        if (*pa != *pb){
            result = false;
            break;
        }
    }
    return(result);
}
static i32
block_compare(void *a, void *b, umem size){
    i32 result = 0;
    for (u8 *pa = (u8*)a, *pb = (u8*)b, *ea = pa + size; pa < ea; pa += 1, pb += 1){
        i32 dif = (i32)*pa - (i32)*pb;
        if (dif != 0){
            result = (dif > 0)?1:-1;
            break;
        }
    }
    return(result);
}
static void
block_fill_u8(void *a, umem size, u8 val){
    for (u8 *ptr = (u8*)a, *e = ptr + size; ptr < e; ptr += 1){
        *ptr = val;
    }
}
static void
block_fill_u16(void *a, umem size, u16 val){
    Assert(size%sizeof(u16) == 0);
    umem count = size/sizeof(u16);
    for (u16 *ptr = (u16*)a, *e = ptr + count; ptr < e; ptr += 1){
        *ptr = val;
    }
}
static void
block_fill_u32(void *a, umem size, u32 val){
    Assert(size%sizeof(u32) == 0);
    umem count = size/sizeof(u32);
    for (u32 *ptr = (u32*)a, *e = ptr + count; ptr < e; ptr += 1){
        *ptr = val;
    }
}
static void
block_fill_u64(void *a, umem size, u64 val){
    Assert(size%sizeof(u64) == 0);
    umem count = size/sizeof(u64);
    for (u64 *ptr = (u64*)a, *e = ptr + count; ptr < e; ptr += 1){
        *ptr = val;
    }
}

#define block_zero_struct(p) block_zero((p), sizeof(*(p)))
#define block_zero_array(a) block_zero((a), sizeof(a))

#define block_copy_struct(d,s) block_copy((d), (s), sizeof(*(d)))
#define block_copy_array(d,s) block_copy((d), (s), sizeof(d))
#define block_copy_dynamic_array(d,s,c) block_copy((d), (s), sizeof(*(d))*(c))

#define block_match_struct(a,b) block_match((a), (b), sizeof(*(a)))
#define block_match_array(a,b) block_match((a), (b), sizeof(a))

////////////////////////////////

static f32
abs_f32(f32 x){
    if (x < 0){
        x = -x;
    }
    return(x);
}

#if C_MATH
#include <math.h>

static f32
mod_f32(f32 x, i32 m){
    f32 whole;
    f32 frac = modff(x, &whole);
    f32 r = ((i32)(whole) % m) + frac;
    return(r);
}
#endif

////////////////////////////////

static Vec2_i8
V2i8(i8 x, i8 y){
    Vec2_i8 v = {x, y};
    return(v);
}
static Vec3_i8
V3i8(i8 x, i8 y, i8 z){
    Vec3_i8 v = {x, y, z};
    return(v);
}
static Vec4_i8
V4i8(i8 x, i8 y, i8 z, i8 w){
    Vec4_i8 v = {x, y, z, w};
    return(v);
}
static Vec2_i16
V2i16(i16 x, i16 y){
    Vec2_i16 v = {x, y};
    return(v);
}
static Vec3_i16
V3i16(i16 x, i16 y, i16 z){
    Vec3_i16 v = {x, y, z};
    return(v);
}
static Vec4_i16
V4i16(i16 x, i16 y, i16 z, i16 w){
    Vec4_i16 v = {x, y, z, w};
    return(v);
}
static Vec2_i32
V2i32(i32 x, i32 y){
    Vec2_i32 v = {x, y};
    return(v);
}
static Vec3_i32
V3i32(i32 x, i32 y, i32 z){
    Vec3_i32 v = {x, y, z};
    return(v);
}
static Vec4_i32
V4i32(i32 x, i32 y, i32 z, i32 w){
    Vec4_i32 v = {x, y, z, w};
    return(v);
}
static Vec2_f32
V2f32(f32 x, f32 y){
    Vec2_f32 v = {x, y};
    return(v);
}
static Vec3_f32
V3f32(f32 x, f32 y, f32 z){
    Vec3_f32 v = {x, y, z};
    return(v);
}
static Vec4_f32
V4f32(f32 x, f32 y, f32 z, f32 w){
    Vec4_f32 v = {x, y, z, w};
    return(v);
}

static Vec2_i8
V2i8(Vec2_i8 o){
    return(V2i8((i8)o.x, (i8)o.y));
}
static Vec2_i8
V2i8(Vec2_i16 o){
    return(V2i8((i8)o.x, (i8)o.y));
}
static Vec2_i8
V2i8(Vec2_i32 o){
    return(V2i8((i8)o.x, (i8)o.y));
}
static Vec2_i8
V2i8(Vec2_f32 o){
    return(V2i8((i8)o.x, (i8)o.y));
}
static Vec3_i8
V3i8(Vec3_i8 o){
    return(V3i8((i8)o.x, (i8)o.y, (i8)o.z));
}
static Vec3_i8
V3i8(Vec3_i16 o){
    return(V3i8((i8)o.x, (i8)o.y, (i8)o.z));
}
static Vec3_i8
V3i8(Vec3_i32 o){
    return(V3i8((i8)o.x, (i8)o.y, (i8)o.z));
}
static Vec3_i8
V3i8(Vec3_f32 o){
    return(V3i8((i8)o.x, (i8)o.y, (i8)o.z));
}
static Vec4_i8
V4i8(Vec4_i8 o){
    return(V4i8((i8)o.x, (i8)o.y, (i8)o.z, (i8)o.w));
}
static Vec4_i8
V4i8(Vec4_i16 o){
    return(V4i8((i8)o.x, (i8)o.y, (i8)o.z, (i8)o.w));
}
static Vec4_i8
V4i8(Vec4_i32 o){
    return(V4i8((i8)o.x, (i8)o.y, (i8)o.z, (i8)o.w));
}
static Vec4_i8
V4i8(Vec4_f32 o){
    return(V4i8((i8)o.x, (i8)o.y, (i8)o.z, (i8)o.w));
}
static Vec2_i16
V2i16(Vec2_i8 o){
    return(V2i16((i16)o.x, (i16)o.y));
}
static Vec2_i16
V2i16(Vec2_i16 o){
    return(V2i16((i16)o.x, (i16)o.y));
}
static Vec2_i16
V2i16(Vec2_i32 o){
    return(V2i16((i16)o.x, (i16)o.y));
}
static Vec2_i16
V2i16(Vec2_f32 o){
    return(V2i16((i16)o.x, (i16)o.y));
}
static Vec3_i16
V3i16(Vec3_i8 o){
    return(V3i16((i16)o.x, (i16)o.y, (i16)o.z));
}
static Vec3_i16
V3i16(Vec3_i16 o){
    return(V3i16((i16)o.x, (i16)o.y, (i16)o.z));
}
static Vec3_i16
V3i16(Vec3_i32 o){
    return(V3i16((i16)o.x, (i16)o.y, (i16)o.z));
}
static Vec3_i16
V3i16(Vec3_f32 o){
    return(V3i16((i16)o.x, (i16)o.y, (i16)o.z));
}
static Vec4_i16
V4i16(Vec4_i8 o){
    return(V4i16((i16)o.x, (i16)o.y, (i16)o.z, (i16)o.w));
}
static Vec4_i16
V4i16(Vec4_i16 o){
    return(V4i16((i16)o.x, (i16)o.y, (i16)o.z, (i16)o.w));
}
static Vec4_i16
V4i16(Vec4_i32 o){
    return(V4i16((i16)o.x, (i16)o.y, (i16)o.z, (i16)o.w));
}
static Vec4_i16
V4i16(Vec4_f32 o){
    return(V4i16((i16)o.x, (i16)o.y, (i16)o.z, (i16)o.w));
}
static Vec2_i32
V2i32(Vec2_i8 o){
    return(V2i32((i32)o.x, (i32)o.y));
}
static Vec2_i32
V2i32(Vec2_i16 o){
    return(V2i32((i32)o.x, (i32)o.y));
}
static Vec2_i32
V2i32(Vec2_i32 o){
    return(V2i32((i32)o.x, (i32)o.y));
}
static Vec2_i32
V2i32(Vec2_f32 o){
    return(V2i32((i32)o.x, (i32)o.y));
}
static Vec3_i32
V3i32(Vec3_i8 o){
    return(V3i32((i32)o.x, (i32)o.y, (i32)o.z));
}
static Vec3_i32
V3i32(Vec3_i16 o){
    return(V3i32((i32)o.x, (i32)o.y, (i32)o.z));
}
static Vec3_i32
V3i32(Vec3_i32 o){
    return(V3i32((i32)o.x, (i32)o.y, (i32)o.z));
}
static Vec3_i32
V3i32(Vec3_f32 o){
    return(V3i32((i32)o.x, (i32)o.y, (i32)o.z));
}
static Vec4_i32
V4i32(Vec4_i8 o){
    return(V4i32((i32)o.x, (i32)o.y, (i32)o.z, (i32)o.w));
}
static Vec4_i32
V4i32(Vec4_i16 o){
    return(V4i32((i32)o.x, (i32)o.y, (i32)o.z, (i32)o.w));
}
static Vec4_i32
V4i32(Vec4_i32 o){
    return(V4i32((i32)o.x, (i32)o.y, (i32)o.z, (i32)o.w));
}
static Vec4_i32
V4i32(Vec4_f32 o){
    return(V4i32((i32)o.x, (i32)o.y, (i32)o.z, (i32)o.w));
}
static Vec2_f32
V2f32(Vec2_i8 o){
    return(V2f32((f32)o.x, (f32)o.y));
}
static Vec2_f32
V2f32(Vec2_i16 o){
    return(V2f32((f32)o.x, (f32)o.y));
}
static Vec2_f32
V2f32(Vec2_i32 o){
    return(V2f32((f32)o.x, (f32)o.y));
}
static Vec2_f32
V2f32(Vec2_f32 o){
    return(V2f32((f32)o.x, (f32)o.y));
}
static Vec3_f32
V3f32(Vec3_i8 o){
    return(V3f32((f32)o.x, (f32)o.y, (f32)o.z));
}
static Vec3_f32
V3f32(Vec3_i16 o){
    return(V3f32((f32)o.x, (f32)o.y, (f32)o.z));
}
static Vec3_f32
V3f32(Vec3_i32 o){
    return(V3f32((f32)o.x, (f32)o.y, (f32)o.z));
}
static Vec3_f32
V3f32(Vec3_f32 o){
    return(V3f32((f32)o.x, (f32)o.y, (f32)o.z));
}
static Vec4_f32
V4f32(Vec4_i8 o){
    return(V4f32((f32)o.x, (f32)o.y, (f32)o.z, (f32)o.w));
}
static Vec4_f32
V4f32(Vec4_i16 o){
    return(V4f32((f32)o.x, (f32)o.y, (f32)o.z, (f32)o.w));
}
static Vec4_f32
V4f32(Vec4_i32 o){
    return(V4f32((f32)o.x, (f32)o.y, (f32)o.z, (f32)o.w));
}
static Vec4_f32
V4f32(Vec4_f32 o){
    return(V4f32((f32)o.x, (f32)o.y, (f32)o.z, (f32)o.w));
}

#define V2 V2f32
#define V3 V3f32
#define V4 V4f32

static Vec2_i8
operator+(Vec2_i8 a, Vec2_i8 b){
    a.x += b.x;
    a.y += b.y;
    return(a);
}
static Vec3_i8
operator+(Vec3_i8 a, Vec3_i8 b){
    a.x += b.x;
    a.y += b.y;
    a.z += b.z;
    return(a);
}
static Vec4_i8
operator+(Vec4_i8 a, Vec4_i8 b){
    a.x += b.x;
    a.y += b.y;
    a.z += b.z;
    a.w += b.w;
    return(a);
}
static Vec2_i16
operator+(Vec2_i16 a, Vec2_i16 b){
    a.x += b.x;
    a.y += b.y;
    return(a);
}
static Vec3_i16
operator+(Vec3_i16 a, Vec3_i16 b){
    a.x += b.x;
    a.y += b.y;
    a.z += b.z;
    return(a);
}
static Vec4_i16
operator+(Vec4_i16 a, Vec4_i16 b){
    a.x += b.x;
    a.y += b.y;
    a.z += b.z;
    a.w += b.w;
    return(a);
}
static Vec2_i32
operator+(Vec2_i32 a, Vec2_i32 b){
    a.x += b.x;
    a.y += b.y;
    return(a);
}
static Vec3_i32
operator+(Vec3_i32 a, Vec3_i32 b){
    a.x += b.x;
    a.y += b.y;
    a.z += b.z;
    return(a);
}
static Vec4_i32
operator+(Vec4_i32 a, Vec4_i32 b){
    a.x += b.x;
    a.y += b.y;
    a.z += b.z;
    a.w += b.w;
    return(a);
}
static Vec2_f32
operator+(Vec2_f32 a, Vec2_f32 b){
    a.x += b.x;
    a.y += b.y;
    return(a);
}
static Vec3_f32
operator+(Vec3_f32 a, Vec3_f32 b){
    a.x += b.x;
    a.y += b.y;
    a.z += b.z;
    return(a);
}
static Vec4_f32
operator+(Vec4_f32 a, Vec4_f32 b){
    a.x += b.x;
    a.y += b.y;
    a.z += b.z;
    a.w += b.w;
    return(a);
}

static Vec2_i8&
operator+=(Vec2_i8 &a, Vec2_i8 b){
    a.x += b.x;
    a.y += b.y;
    return(a);
}
static Vec3_i8&
operator+=(Vec3_i8 &a, Vec3_i8 b){
    a.x += b.x;
    a.y += b.y;
    a.z += b.z;
    return(a);
}
static Vec4_i8&
operator+=(Vec4_i8 &a, Vec4_i8 b){
    a.x += b.x;
    a.y += b.y;
    a.z += b.z;
    a.w += b.w;
    return(a);
}
static Vec2_i16&
operator+=(Vec2_i16 &a, Vec2_i16 b){
    a.x += b.x;
    a.y += b.y;
    return(a);
}
static Vec3_i16&
operator+=(Vec3_i16 &a, Vec3_i16 b){
    a.x += b.x;
    a.y += b.y;
    a.z += b.z;
    return(a);
}
static Vec4_i16&
operator+=(Vec4_i16 &a, Vec4_i16 b){
    a.x += b.x;
    a.y += b.y;
    a.z += b.z;
    a.w += b.w;
    return(a);
}
static Vec2_i32&
operator+=(Vec2_i32 &a, Vec2_i32 b){
    a.x += b.x;
    a.y += b.y;
    return(a);
}
static Vec3_i32&
operator+=(Vec3_i32 &a, Vec3_i32 b){
    a.x += b.x;
    a.y += b.y;
    a.z += b.z;
    return(a);
}
static Vec4_i32&
operator+=(Vec4_i32 &a, Vec4_i32 b){
    a.x += b.x;
    a.y += b.y;
    a.z += b.z;
    a.w += b.w;
    return(a);
}
static Vec2_f32&
operator+=(Vec2_f32 &a, Vec2_f32 b){
    a.x += b.x;
    a.y += b.y;
    return(a);
}
static Vec3_f32&
operator+=(Vec3_f32 &a, Vec3_f32 b){
    a.x += b.x;
    a.y += b.y;
    a.z += b.z;
    return(a);
}
static Vec4_f32&
operator+=(Vec4_f32 &a, Vec4_f32 b){
    a.x += b.x;
    a.y += b.y;
    a.z += b.z;
    a.w += b.w;
    return(a);
}

static Vec2_i8
operator-(Vec2_i8 a, Vec2_i8 b){
    a.x -= b.x;
    a.y -= b.y;
    return(a);
}
static Vec3_i8
operator-(Vec3_i8 a, Vec3_i8 b){
    a.x -= b.x;
    a.y -= b.y;
    a.z -= b.z;
    return(a);
}
static Vec4_i8
operator-(Vec4_i8 a, Vec4_i8 b){
    a.x -= b.x;
    a.y -= b.y;
    a.z -= b.z;
    a.w -= b.w;
    return(a);
}
static Vec2_i16
operator-(Vec2_i16 a, Vec2_i16 b){
    a.x -= b.x;
    a.y -= b.y;
    return(a);
}
static Vec3_i16
operator-(Vec3_i16 a, Vec3_i16 b){
    a.x -= b.x;
    a.y -= b.y;
    a.z -= b.z;
    return(a);
}
static Vec4_i16
operator-(Vec4_i16 a, Vec4_i16 b){
    a.x -= b.x;
    a.y -= b.y;
    a.z -= b.z;
    a.w -= b.w;
    return(a);
}
static Vec2_i32
operator-(Vec2_i32 a, Vec2_i32 b){
    a.x -= b.x;
    a.y -= b.y;
    return(a);
}
static Vec3_i32
operator-(Vec3_i32 a, Vec3_i32 b){
    a.x -= b.x;
    a.y -= b.y;
    a.z -= b.z;
    return(a);
}
static Vec4_i32
operator-(Vec4_i32 a, Vec4_i32 b){
    a.x -= b.x;
    a.y -= b.y;
    a.z -= b.z;
    a.w -= b.w;
    return(a);
}
static Vec2_f32
operator-(Vec2_f32 a, Vec2_f32 b){
    a.x -= b.x;
    a.y -= b.y;
    return(a);
}
static Vec3_f32
operator-(Vec3_f32 a, Vec3_f32 b){
    a.x -= b.x;
    a.y -= b.y;
    a.z -= b.z;
    return(a);
}
static Vec4_f32
operator-(Vec4_f32 a, Vec4_f32 b){
    a.x -= b.x;
    a.y -= b.y;
    a.z -= b.z;
    a.w -= b.w;
    return(a);
}

static Vec2_i8&
operator-=(Vec2_i8 &a, Vec2_i8 b){
    a.x -= b.x;
    a.y -= b.y;
    return(a);
}
static Vec3_i8&
operator-=(Vec3_i8 &a, Vec3_i8 b){
    a.x -= b.x;
    a.y -= b.y;
    a.z -= b.z;
    return(a);
}
static Vec4_i8&
operator-=(Vec4_i8 &a, Vec4_i8 b){
    a.x -= b.x;
    a.y -= b.y;
    a.z -= b.z;
    a.w -= b.w;
    return(a);
}
static Vec2_i16&
operator-=(Vec2_i16 &a, Vec2_i16 b){
    a.x -= b.x;
    a.y -= b.y;
    return(a);
}
static Vec3_i16&
operator-=(Vec3_i16 &a, Vec3_i16 b){
    a.x -= b.x;
    a.y -= b.y;
    a.z -= b.z;
    return(a);
}
static Vec4_i16&
operator-=(Vec4_i16 &a, Vec4_i16 b){
    a.x -= b.x;
    a.y -= b.y;
    a.z -= b.z;
    a.w -= b.w;
    return(a);
}
static Vec2_i32&
operator-=(Vec2_i32 &a, Vec2_i32 b){
    a.x -= b.x;
    a.y -= b.y;
    return(a);
}
static Vec3_i32&
operator-=(Vec3_i32 &a, Vec3_i32 b){
    a.x -= b.x;
    a.y -= b.y;
    a.z -= b.z;
    return(a);
}
static Vec4_i32&
operator-=(Vec4_i32 &a, Vec4_i32 b){
    a.x -= b.x;
    a.y -= b.y;
    a.z -= b.z;
    a.w -= b.w;
    return(a);
}
static Vec2_f32&
operator-=(Vec2_f32 &a, Vec2_f32 b){
    a.x -= b.x;
    a.y -= b.y;
    return(a);
}
static Vec3_f32&
operator-=(Vec3_f32 &a, Vec3_f32 b){
    a.x -= b.x;
    a.y -= b.y;
    a.z -= b.z;
    return(a);
}
static Vec4_f32&
operator-=(Vec4_f32 &a, Vec4_f32 b){
    a.x -= b.x;
    a.y -= b.y;
    a.z -= b.z;
    a.w -= b.w;
    return(a);
}

static Vec2_i8
operator*(i8 s, Vec2_i8 v){
    v.x *= s;
    v.y *= s;
    return(v);
}
static Vec2_i8
operator*(Vec2_i8 v, i8 s){
    v.x *= s;
    v.y *= s;
    return(v);
}
static Vec3_i8
operator*(i8 s, Vec3_i8 v){
    v.x *= s;
    v.y *= s;
    v.z *= s;
    return(v);
}
static Vec3_i8
operator*(Vec3_i8 v, i8 s){
    v.x *= s;
    v.y *= s;
    v.z *= s;
    return(v);
}
static Vec4_i8
operator*(i8 s, Vec4_i8 v){
    v.x *= s;
    v.y *= s;
    v.z *= s;
    v.w *= s;
    return(v);
}
static Vec4_i8
operator*(Vec4_i8 v, i8 s){
    v.x *= s;
    v.y *= s;
    v.z *= s;
    v.w *= s;
    return(v);
}
static Vec2_i16
operator*(i16 s, Vec2_i16 v){
    v.x *= s;
    v.y *= s;
    return(v);
}
static Vec2_i16
operator*(Vec2_i16 v, i16 s){
    v.x *= s;
    v.y *= s;
    return(v);
}
static Vec3_i16
operator*(i16 s, Vec3_i16 v){
    v.x *= s;
    v.y *= s;
    v.z *= s;
    return(v);
}
static Vec3_i16
operator*(Vec3_i16 v, i16 s){
    v.x *= s;
    v.y *= s;
    v.z *= s;
    return(v);
}
static Vec4_i16
operator*(i16 s, Vec4_i16 v){
    v.x *= s;
    v.y *= s;
    v.z *= s;
    v.w *= s;
    return(v);
}
static Vec4_i16
operator*(Vec4_i16 v, i16 s){
    v.x *= s;
    v.y *= s;
    v.z *= s;
    v.w *= s;
    return(v);
}
static Vec2_i32
operator*(i32 s, Vec2_i32 v){
    v.x *= s;
    v.y *= s;
    return(v);
}
static Vec2_i32
operator*(Vec2_i32 v, i32 s){
    v.x *= s;
    v.y *= s;
    return(v);
}
static Vec3_i32
operator*(i32 s, Vec3_i32 v){
    v.x *= s;
    v.y *= s;
    v.z *= s;
    return(v);
}
static Vec3_i32
operator*(Vec3_i32 v, i32 s){
    v.x *= s;
    v.y *= s;
    v.z *= s;
    return(v);
}
static Vec4_i32
operator*(i32 s, Vec4_i32 v){
    v.x *= s;
    v.y *= s;
    v.z *= s;
    v.w *= s;
    return(v);
}
static Vec4_i32
operator*(Vec4_i32 v, i32 s){
    v.x *= s;
    v.y *= s;
    v.z *= s;
    v.w *= s;
    return(v);
}
static Vec2_f32
operator*(f32 s, Vec2_f32 v){
    v.x *= s;
    v.y *= s;
    return(v);
}
static Vec2_f32
operator*(Vec2_f32 v, f32 s){
    v.x *= s;
    v.y *= s;
    return(v);
}
static Vec3_f32
operator*(f32 s, Vec3_f32 v){
    v.x *= s;
    v.y *= s;
    v.z *= s;
    return(v);
}
static Vec3_f32
operator*(Vec3_f32 v, f32 s){
    v.x *= s;
    v.y *= s;
    v.z *= s;
    return(v);
}
static Vec4_f32
operator*(f32 s, Vec4_f32 v){
    v.x *= s;
    v.y *= s;
    v.z *= s;
    v.w *= s;
    return(v);
}
static Vec4_f32
operator*(Vec4_f32 v, f32 s){
    v.x *= s;
    v.y *= s;
    v.z *= s;
    v.w *= s;
    return(v);
}

static Vec2_i8&
operator*=(Vec2_i8 &v, i8 s){
    v.x *= s;
    v.y *= s;
    return(v);
}
static Vec3_i8&
operator*=(Vec3_i8 &v, i8 s){
    v.x *= s;
    v.y *= s;
    v.z *= s;
    return(v);
}
static Vec4_i8&
operator*=(Vec4_i8 &v, i8 s){
    v.x *= s;
    v.y *= s;
    v.z *= s;
    v.w *= s;
    return(v);
}
static Vec2_i16&
operator*=(Vec2_i16 &v, i16 s){
    v.x *= s;
    v.y *= s;
    return(v);
}
static Vec3_i16&
operator*=(Vec3_i16 &v, i16 s){
    v.x *= s;
    v.y *= s;
    v.z *= s;
    return(v);
}
static Vec4_i16&
operator*=(Vec4_i16 &v, i16 s){
    v.x *= s;
    v.y *= s;
    v.z *= s;
    v.w *= s;
    return(v);
}
static Vec2_i32&
operator*=(Vec2_i32 &v, i32 s){
    v.x *= s;
    v.y *= s;
    return(v);
}
static Vec3_i32&
operator*=(Vec3_i32 &v, i32 s){
    v.x *= s;
    v.y *= s;
    v.z *= s;
    return(v);
}
static Vec4_i32&
operator*=(Vec4_i32 &v, i32 s){
    v.x *= s;
    v.y *= s;
    v.z *= s;
    v.w *= s;
    return(v);
}
static Vec2_f32&
operator*=(Vec2_f32 &v, f32 s){
    v.x *= s;
    v.y *= s;
    return(v);
}
static Vec3_f32&
operator*=(Vec3_f32 &v, f32 s){
    v.x *= s;
    v.y *= s;
    v.z *= s;
    return(v);
}
static Vec4_f32&
operator*=(Vec4_f32 &v, f32 s){
    v.x *= s;
    v.y *= s;
    v.z *= s;
    v.w *= s;
    return(v);
}

static Vec2_i8
operator/(Vec2_i8 v, i8 s){
    v.x /= s;
    v.y /= s;
    return(v);
}
static Vec3_i8
operator/(Vec3_i8 v, i8 s){
    v.x /= s;
    v.y /= s;
    v.z /= s;
    return(v);
}
static Vec4_i8
operator/(Vec4_i8 v, i8 s){
    v.x /= s;
    v.y /= s;
    v.z /= s;
    v.w /= s;
    return(v);
}
static Vec2_i16
operator/(Vec2_i16 v, i16 s){
    v.x /= s;
    v.y /= s;
    return(v);
}
static Vec3_i16
operator/(Vec3_i16 v, i16 s){
    v.x /= s;
    v.y /= s;
    v.z /= s;
    return(v);
}
static Vec4_i16
operator/(Vec4_i16 v, i16 s){
    v.x /= s;
    v.y /= s;
    v.z /= s;
    v.w /= s;
    return(v);
}
static Vec2_i32
operator/(Vec2_i32 v, i32 s){
    v.x /= s;
    v.y /= s;
    return(v);
}
static Vec3_i32
operator/(Vec3_i32 v, i32 s){
    v.x /= s;
    v.y /= s;
    v.z /= s;
    return(v);
}
static Vec4_i32
operator/(Vec4_i32 v, i32 s){
    v.x /= s;
    v.y /= s;
    v.z /= s;
    v.w /= s;
    return(v);
}
static Vec2_f32
operator/(Vec2_f32 v, f32 s){
    v.x /= s;
    v.y /= s;
    return(v);
}
static Vec3_f32
operator/(Vec3_f32 v, f32 s){
    v.x /= s;
    v.y /= s;
    v.z /= s;
    return(v);
}
static Vec4_f32
operator/(Vec4_f32 v, f32 s){
    v.x /= s;
    v.y /= s;
    v.z /= s;
    v.w /= s;
    return(v);
}

static Vec2_i8&
operator/=(Vec2_i8 &v, i8 s){
    v.x /= s;
    v.y /= s;
    return(v);
}
static Vec3_i8&
operator/=(Vec3_i8 &v, i8 s){
    v.x /= s;
    v.y /= s;
    v.z /= s;
    return(v);
}
static Vec4_i8&
operator/=(Vec4_i8 &v, i8 s){
    v.x /= s;
    v.y /= s;
    v.z /= s;
    v.w /= s;
    return(v);
}
static Vec2_i16&
operator/=(Vec2_i16 &v, i16 s){
    v.x /= s;
    v.y /= s;
    return(v);
}
static Vec3_i16&
operator/=(Vec3_i16 &v, i16 s){
    v.x /= s;
    v.y /= s;
    v.z /= s;
    return(v);
}
static Vec4_i16&
operator/=(Vec4_i16 &v, i16 s){
    v.x /= s;
    v.y /= s;
    v.z /= s;
    v.w /= s;
    return(v);
}
static Vec2_i32&
operator/=(Vec2_i32 &v, i32 s){
    v.x /= s;
    v.y /= s;
    return(v);
}
static Vec3_i32&
operator/=(Vec3_i32 &v, i32 s){
    v.x /= s;
    v.y /= s;
    v.z /= s;
    return(v);
}
static Vec4_i32&
operator/=(Vec4_i32 &v, i32 s){
    v.x /= s;
    v.y /= s;
    v.z /= s;
    v.w /= s;
    return(v);
}
static Vec2_f32&
operator/=(Vec2_f32 &v, f32 s){
    v.x /= s;
    v.y /= s;
    return(v);
}
static Vec3_f32&
operator/=(Vec3_f32 &v, f32 s){
    v.x /= s;
    v.y /= s;
    v.z /= s;
    return(v);
}
static Vec4_f32&
operator/=(Vec4_f32 &v, f32 s){
    v.x /= s;
    v.y /= s;
    v.z /= s;
    v.w /= s;
    return(v);
}

static b32
operator==(Vec2_i8 a, Vec2_i8 b){
    return(a.x == b.x && a.y == b.y);
}
static b32
operator==(Vec3_i8 a, Vec3_i8 b){
    return(a.x == b.x && a.y == b.y && a.z == b.z);
}
static b32
operator==(Vec4_i8 a, Vec4_i8 b){
    return(a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w);
}
static b32
operator==(Vec2_i16 a, Vec2_i16 b){
    return(a.x == b.x && a.y == b.y);
}
static b32
operator==(Vec3_i16 a, Vec3_i16 b){
    return(a.x == b.x && a.y == b.y && a.z == b.z);
}
static b32
operator==(Vec4_i16 a, Vec4_i16 b){
    return(a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w);
}
static b32
operator==(Vec2_i32 a, Vec2_i32 b){
    return(a.x == b.x && a.y == b.y);
}
static b32
operator==(Vec3_i32 a, Vec3_i32 b){
    return(a.x == b.x && a.y == b.y && a.z == b.z);
}
static b32
operator==(Vec4_i32 a, Vec4_i32 b){
    return(a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w);
}
static b32
operator==(Vec2_f32 a, Vec2_f32 b){
    return(a.x == b.x && a.y == b.y);
}
static b32
operator==(Vec3_f32 a, Vec3_f32 b){
    return(a.x == b.x && a.y == b.y && a.z == b.z);
}
static b32
operator==(Vec4_f32 a, Vec4_f32 b){
    return(a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w);
}

static b32
operator!=(Vec2_i8 a, Vec2_i8 b){
    return(a.x != b.x || a.y != b.y);
}
static b32
operator!=(Vec3_i8 a, Vec3_i8 b){
    return(a.x != b.x || a.y != b.y || a.z != b.z);
}
static b32
operator!=(Vec4_i8 a, Vec4_i8 b){
    return(a.x != b.x || a.y != b.y || a.z != b.z || a.w != b.w);
}
static b32
operator!=(Vec2_i16 a, Vec2_i16 b){
    return(a.x != b.x || a.y != b.y);
}
static b32
operator!=(Vec3_i16 a, Vec3_i16 b){
    return(a.x != b.x || a.y != b.y || a.z != b.z);
}
static b32
operator!=(Vec4_i16 a, Vec4_i16 b){
    return(a.x != b.x || a.y != b.y || a.z != b.z || a.w != b.w);
}
static b32
operator!=(Vec2_i32 a, Vec2_i32 b){
    return(a.x != b.x || a.y != b.y);
}
static b32
operator!=(Vec3_i32 a, Vec3_i32 b){
    return(a.x != b.x || a.y != b.y || a.z != b.z);
}
static b32
operator!=(Vec4_i32 a, Vec4_i32 b){
    return(a.x != b.x || a.y != b.y || a.z != b.z || a.w != b.w);
}
static b32
operator!=(Vec2_f32 a, Vec2_f32 b){
    return(a.x != b.x || a.y != b.y);
}
static b32
operator!=(Vec3_f32 a, Vec3_f32 b){
    return(a.x != b.x || a.y != b.y || a.z != b.z);
}
static b32
operator!=(Vec4_f32 a, Vec4_f32 b){
    return(a.x != b.x || a.y != b.y || a.z != b.z || a.w != b.w);
}

////////////////////////////////

static f32
lerp(f32 a, f32 t, f32 b){
    return(a + (b-a)*t);
}

static i32
lerp(i32 a, f32 t, i32 b){
    return((i32)(lerp((f32)a, t, (f32)b)));
}

static Vec2
lerp(Vec2 a, f32 t, Vec2 b){
    return(a + (b-a)*t);
}

static Vec3
lerp(Vec3 a, f32 t, Vec3 b){
    return(a + (b-a)*t);
}

static Vec4
lerp(Vec4 a, f32 t, Vec4 b){
    return(a + (b-a)*t);
}

static f32
unlerp(f32 a, f32 x, f32 b){
    f32 r = x;
    if (b != a){
        r = (x - a)/(b - a);
    }
    return(r);
}

////////////////////////////////

// TODO(allen): Convert colors to Vec4
static u32
color_blend(u32 a, f32 t, u32 b){
    union{
        u8 byte[4];
        u32 comp;
    } A, B, R;
    A.comp = a;
    B.comp = b;
    R.byte[0] = (u8)lerp(A.byte[0], t, B.byte[0]);
    R.byte[1] = (u8)lerp(A.byte[1], t, B.byte[1]);
    R.byte[2] = (u8)lerp(A.byte[2], t, B.byte[2]);
    R.byte[3] = (u8)lerp(A.byte[3], t, B.byte[3]);
    return(R.comp);
}

static Vec3
unpack_color3(u32 color){
    Vec3 result;
    result.r = ((color >> 16) & 0xFF)/255.f;
    result.g = ((color >> 8) & 0xFF)/255.f;
    result.b = ((color >> 0) & 0xFF)/255.f;
    return(result);
}

static Vec4
unpack_color4(u32 color){
    Vec4 result;
    result.a = ((color >> 24) & 0xFF)/255.f;
    result.r = ((color >> 16) & 0xFF)/255.f;
    result.g = ((color >> 8) & 0xFF)/255.f;
    result.b = ((color >> 0) & 0xFF)/255.f;
    return(result);
}

static u32
pack_color4(Vec4 color){
    u32 result =
        ((u8)(color.a*255) << 24) |
        ((u8)(color.r*255) << 16) |
        ((u8)(color.g*255) << 8) |
        ((u8)(color.b*255) << 0);
    return(result);
}

static Vec4
rgba_to_hsla(Vec4 rgba){
    Vec4 hsla = {};
    f32 max, min, delta;
    i32 maxc;
    hsla.a = rgba.a;
    max = rgba.r; min = rgba.r;
    maxc = 0;
    if (rgba.r < rgba.g){
        max = rgba.g;
        maxc = 1;
    }
    if (rgba.b > max){
        max = rgba.b;
        maxc = 2;
    }
    if (rgba.r > rgba.g){
        min = rgba.g;
    }
    if (rgba.b < min){
        min = rgba.b;
    }
    delta = max - min;
    
    hsla.z = (max + min)*.5f;
    if (delta == 0){
        hsla.x = 0.f;
        hsla.y = 0.f;
    }
    else{
        switch (maxc){
            case 0:
            {
                hsla.x = (rgba.g - rgba.b) / delta;
                hsla.x += (rgba.g < rgba.b)*6.f;
            }break;
            
            case 1:
            {
                hsla.x = (rgba.b - rgba.r) / delta;
                hsla.x += 2.f;
            }break;
            
            case 2:
            {
                hsla.x = (rgba.r - rgba.g) / delta;
                hsla.x += 4.f;
            }break;
        }
        hsla.x *= (1/6.f); //*60 / 360
        hsla.y = delta / (1.f - abs_f32(2.f*hsla.z - 1.f));
    }
    
    return(hsla);
}

static Vec4
hsla_to_rgba(Vec4 hsla){
    if (hsla.h >= 1.f){
        hsla.h = 0.f;
    }
    f32 C = (1.f - abs_f32(2*hsla.z - 1.f))*hsla.y;
    f32 X = C*(1.f-abs_f32(mod_f32(hsla.x*6.f, 2)-1.f));
    f32 m = hsla.z - C*.5f;
    i32 H = floor32(hsla.x*6.f);
    Vec4 rgba = {};
    rgba.a = hsla.a;
    switch (H){
        case 0: rgba.r = C; rgba.g = X; rgba.b = 0; break;
        case 1: rgba.r = X; rgba.g = C; rgba.b = 0; break;
        case 2: rgba.r = 0; rgba.g = C; rgba.b = X; break;
        case 3: rgba.r = 0; rgba.g = X; rgba.b = C; break;
        case 4: rgba.r = X; rgba.g = 0; rgba.b = C; break;
        case 5: rgba.r = C; rgba.g = 0; rgba.b = X; break;
    }
    rgba.r += m;
    rgba.g += m;
    rgba.b += m;
    return(rgba);
}

////////////////////////////////

static Interval_i8
Ii8(i8 a, i8 b){
    Interval_i8 interval = {a, b};
    if (b < a){
        interval.min = b;
        interval.max = a;
    }
    return(interval);
}
static Interval_i16
Ii16(i16 a, i16 b){
    Interval_i16 interval = {a, b};
    if (b < a){
        interval.min = b;
        interval.max = a;
    }
    return(interval);
}
static Interval_i32
Ii32(i32 a, i32 b){
    Interval_i32 interval = {a, b};
    if (b < a){
        interval.min = b;
        interval.max = a;
    }
    return(interval);
}
static Interval_f32
If32(f32 a, f32 b){
    Interval_f32 interval = {a, b};
    if (b < a){
        interval.min = b;
        interval.max = a;
    }
    return(interval);
}

static Interval_i8
range_margin(Interval_i8 range, i8 margin){
    range.min += margin;
    range.max -= margin;
    return(range);
}
static Interval_i16
range_margin(Interval_i16 range, i16 margin){
    range.min += margin;
    range.max -= margin;
    return(range);
}
static Interval_i32
range_margin(Interval_i32 range, i32 margin){
    range.min += margin;
    range.max -= margin;
    return(range);
}
static Interval_f32
range_margin(Interval_f32 range, f32 margin){
    range.min += margin;
    range.max -= margin;
    return(range);
}

static i8
range_size(Interval_i8 range){
    return(range.max - range.min);
}
static i16
range_size(Interval_i16 range){
    return(range.max - range.min);
}
static i32
range_size(Interval_i32 range){
    return(range.max - range.min);
}
static f32
range_size(Interval_f32 range){
    return(range.max - range.min);
}

static i32
get_width(Range range){
    i32 result = range.end - range.start;
    if (result < 0){
        result = 0;
    }
    return(result);
}

static Range_i8
make_range_i8(i8 p1, i8 p2){
    Range_i8 range;
    if (p1 < p2){
        range.min = p1;
        range.max = p2;
    }
    else{
        range.min = p2;
        range.max = p1;
    }
    return(range);
}
static Range_i16
make_range_i16(i16 p1, i16 p2){
    Range_i16 range;
    if (p1 < p2){
        range.min = p1;
        range.max = p2;
    }
    else{
        range.min = p2;
        range.max = p1;
    }
    return(range);
}
static Range_i32
make_range_i32(i32 p1, i32 p2){
    Range_i32 range;
    if (p1 < p2){
        range.min = p1;
        range.max = p2;
    }
    else{
        range.min = p2;
        range.max = p1;
    }
    return(range);
}
static Range_f32
make_range_f32(f32 p1, f32 p2){
    Range_f32 range;
    if (p1 < p2){
        range.min = p1;
        range.max = p2;
    }
    else{
        range.min = p2;
        range.max = p1;
    }
    return(range);
}
static Range_umem
make_range_umem(umem p1, umem p2){
    Range_umem range;
    if (p1 < p2){
        range.min = p1;
        range.max = p2;
    }
    else{
        range.min = p2;
        range.max = p1;
    }
    return(range);
}

static Range_i8
make_range_i8(i8 p){
    Range_i8 range = {p, p};
    return(range);
}
static Range_i16
make_range_i16(i16 p){
    Range_i16 range = {p, p};
    return(range);
}
static Range_i32
make_range_i32(i32 p){
    Range_i32 range = {p, p};
    return(range);
}
static Range_f32
make_range_f32(f32 p){
    Range_f32 range = {p, p};
    return(range);
}
static Range_umem
make_range_umem(umem p){
    Range_umem range = {p, p};
    return(range);
}

#define make_range make_range_i32

static Range
rectify(Range range) {
    return(make_range(range.min, range.max));
}

static b32
interval_overlap(i32 a0, i32 a1, i32 b0, i32 b1){
    return(a0 < b1 && b0 < a1);
}

static b32
interval_overlap(Range a, Range b){
    return(interval_overlap(a.first, a.one_past_last, b.first, b.one_past_last));
}

static i32
interval_overlap(f32 a0, f32 a1, f32 b0, f32 b1){
    return(a0 < b1 && b0 < a1);
}

static b32
interval_contains(i32 a0, i32 a1, i32 b){
    return((a0 <= b) && (b < a1));
}

static b32
interval_contains(Range range, i32 b){
    return(interval_contains(range.start, range.one_past_last, b));
}

static Range
clip_range_to_width(Range range, i32 max_width) {
    i32 top = range.first + max_width;
    range.end = clamp_top(range.end, top);
    return(range);
}

static b32
interval_is_valid(Range range){
    return(range.start <= range.one_past_last);
}

static i32
replace_range_compute_shift(i32 replace_start, i32 replace_end, i32 insert_length){
    return(insert_length - (replace_end - replace_start));
}

static i32
replace_range_compute_shift(Range range, i32 insert_length){
    return(replace_range_compute_shift(range.first, range.one_past_last, insert_length));
}

////////////////////////////////

static i32_Rect
i32R(i32 l, i32 t, i32 r, i32 b){
    i32_Rect rect = {};
    rect.x0 = l;
    rect.y0 = t;
    rect.x1 = r;
    rect.y1 = b;
    return(rect);
}

static i32_Rect
i32R_xy_wh(i32 x, i32 y, i32 w, i32 h){
    return(i32R(x, y, x + w, y + h));
}

static i32_Rect
i32R(f32_Rect r){
    i32_Rect rect = {};
    rect.x0 = (i32)r.x0;
    rect.y0 = (i32)r.y0;
    rect.x1 = (i32)r.x1;
    rect.y1 = (i32)r.y1;
    return(rect);
}

static f32_Rect
f32R(f32 l, f32 t, f32 r, f32 b){
    f32_Rect rect = {};
    rect.x0 = l;
    rect.y0 = t;
    rect.x1 = r;
    rect.y1 = b;
    return(rect);
}

static f32_Rect
f32R(Vec2 p0, Vec2 p1){
    f32_Rect rect = {};
    rect.p0 = p0;
    rect.p1 = p1;
    return(rect);
}

static f32_Rect
f32R(i32_Rect r){
    f32_Rect rect = {};
    rect.x0 = (f32)r.x0;
    rect.y0 = (f32)r.y0;
    rect.x1 = (f32)r.x1;
    rect.y1 = (f32)r.y1;
    return(rect);
}

static i32
rect_equal(i32_Rect r1, i32_Rect r2){
    return(r1.x0 == r2.x0 && r1.y0 == r2.y0 && r1.x1 == r2.x1 && r1.y1 == r2.y1);
}

static b32
rect_contains_point(b32 BLAH, f32 x0, f32 y0, f32 x1, f32 y1, f32 x, f32 y){
    return(x0 <= x && x < x1 && y0 <= y && y < y1);
}

static b32
rect_contains_point(b32 BLAH, i32 x0, i32 y0, i32 x1, i32 y1, i32 x, i32 y){
    return(x0 <= x && x < x1 && y0 <= y && y < y1);
}

static b32
rect_contains_point(Rect_f32 rect, Vec2_f32 p){
    return(rect_contains_point(false, rect.x0, rect.y0, rect.x1, rect.y1, p.x, p.y));
}

static b32
rect_contains_point(Rect_i32 rect, Vec2_i32 p){
    return(rect_contains_point(false, rect.x0, rect.y0, rect.x1, rect.y1, p.x, p.y));
}

static i32_Rect
get_inner_rect(i32_Rect outer, i32 margin){
    i32_Rect r = {};
    r.x0 = outer.x0 + margin;
    r.y0 = outer.y0 + margin;
    r.x1 = outer.x1 - margin;
    r.y1 = outer.y1 - margin;
    return(r);
}

static f32_Rect
get_inner_rect(f32_Rect outer, f32 margin){
    f32_Rect r = {};
    r.x0 = outer.x0 + margin;
    r.y0 = outer.y0 + margin;
    r.x1 = outer.x1 - margin;
    r.y1 = outer.y1 - margin;
    return(r);
}

static i32
rect_height(i32_Rect rect){
    return(rect.y1 - rect.y0);
}

static i32
rect_width(i32_Rect rect){
    return(rect.x1 - rect.x0);
}

static i32
fits_inside(i32_Rect rect, i32_Rect outer){
    return(rect.x0 >= outer.x0 && rect.x1 <= outer.x1 && rect.y0 >= outer.y0 && rect.y1 <= outer.y1);
}

static i32
rect_overlap(f32_Rect a, f32_Rect b){
    return(interval_overlap(a.x0, a.x1, b.x0, b.x1) &&
           interval_overlap(a.y0, a.y1, b.y0, b.y1));
}

static f32
rect_height(f32_Rect rect){
    return(rect.y1 - rect.y0);
}

static f32
rect_width(f32_Rect rect){
    return(rect.x1 - rect.x0);
}

static Vec2
rect_dim(f32_Rect rect){
    return(V2(rect.x1 - rect.x0, rect.y1 - rect.y0));
}

static Vec2
rect_center(f32_Rect rect){
    return(V2(0.5f*(rect.x0 + rect.x1), 0.5f*(rect.y0 + rect.y1)));
}

#define center_of rect_center

static i32_Rect
intersection_of(i32_Rect a, i32_Rect b){
    i32_Rect result;
    result.x0 = Max(a.x0, b.x0);
    result.y0 = Max(a.y0, b.y0);
    result.x1 = Min(a.x1, b.x1);
    result.y1 = Min(a.y1, b.y1);
    return(result);
}

static i32_Rect
union_of(i32_Rect a, i32_Rect b){
    i32_Rect result;
    result.x0 = Max(a.x0, b.x0);
    result.y0 = Max(a.y0, b.y0);
    result.x1 = Min(a.x1, b.x1);
    result.y1 = Min(a.y1, b.y1);
    return(result);
}

static f32_Rect
intersection_of(f32_Rect a, f32_Rect b){
    f32_Rect result;
    result.x0 = Max(a.x0, b.x0);
    result.y0 = Max(a.y0, b.y0);
    result.x1 = Min(a.x1, b.x1);
    result.y1 = Min(a.y1, b.y1);
    return(result);
}

static f32_Rect
union_of(f32_Rect a, f32_Rect b){
    f32_Rect result;
    result.x0 = Max(a.x0, b.x0);
    result.y0 = Max(a.y0, b.y0);
    result.x1 = Min(a.x1, b.x1);
    result.y1 = Min(a.y1, b.y1);
    return(result);
}

////////////////////////////////

#if defined(Migrating__Arena)

static void*
base_reserve__noop(void *user_data, umem size, umem *size_out){
    *size_out = 0;
    return(0);
}
static void
base_commit__noop(void *user_data, void *ptr, umem size){}
static void
base_uncommit__noop(void *user_data, void *ptr, umem size){}
static void
base_free__noop(void *user_data, void *ptr){}
static void
base_set_access__noop(void *user_data, void *ptr, umem size, Access_Flag flags){}

static Base_Allocator
make_base_allocator(Base_Allocator_Reserve_Signature *func_reserve,
                    Base_Allocator_Commit_Signature *func_commit,
                    Base_Allocator_Uncommit_Signature *func_uncommit,
                    Base_Allocator_Free_Signature *func_free,
                    Base_Allocator_Set_Access_Signature *func_set_access,
                    void *user_data){
    if (func_reserve == 0){
        func_reserve = base_reserve__noop;
    }
    if (func_commit == 0){
        func_commit = base_commit__noop;
    }
    if (func_uncommit == 0){
        func_uncommit = base_uncommit__noop;
    }
    if (func_free == 0){
        func_free = base_free__noop;
    }
    if (func_set_access == 0){
        func_set_access = base_set_access__noop;
    }
    Base_Allocator base_allocator = {
        func_reserve,
        func_commit,
        func_uncommit,
        func_free,
        func_set_access,
        user_data,
    };
    return(base_allocator);
}
static Data
base_allocate(Base_Allocator *allocator, umem size){
    umem full_size = 0;
    void *memory = allocator->reserve(allocator->user_data, size, &full_size);
    allocator->commit(allocator->user_data, memory, full_size);
    return(make_data(memory, full_size));
}
static void
base_free(Base_Allocator *allocator, void *ptr){
    allocator->free(allocator->user_data, ptr);
}

////////////////////////////////

static Cursor
make_cursor(void *base, umem size){
    Cursor cursor = {(u8*)base, 0, size};
    return(cursor);
}
static Cursor
make_cursor(Data data){
    return(make_cursor(data.data, data.size));
}
static Cursor
make_cursor(Base_Allocator *allocator, umem size){
    Data memory = base_allocate(allocator, size);
    return(make_cursor(memory));
}
static Data
linalloc_push(Cursor *cursor, umem size){
    Data result = {};
    if (cursor->pos + size <= cursor->cap){
        result.data = cursor->base + cursor->pos;
        result.size = size;
        cursor->pos += size;
    }
    return(result);
}
static void
linalloc_pop(Cursor *cursor, umem size){
    if (cursor->pos > size){
        cursor->pos -= size;
    }
    else{
        cursor->pos = 0;
    }
}
static Data
linalloc_align(Cursor *cursor, umem alignment){
    umem pos = round_up_umem(cursor->pos, alignment);
    umem new_size = pos - cursor->pos;
    return(linalloc_push(cursor, new_size));
}
static Temp_Memory_Cursor
linalloc_begin_temp(Cursor *cursor){
    Temp_Memory_Cursor temp = {cursor, cursor->pos};
    return(temp);
}
static void
linalloc_end_temp(Temp_Memory_Cursor temp){
    temp.cursor->pos = temp.pos;
}
static void
linalloc_clear(Cursor *cursor){
    cursor->pos = 0;
}
static Arena
make_arena(Base_Allocator *allocator, umem chunk_size, umem alignment){
    Arena arena = {allocator, 0, chunk_size, alignment};
    return(arena);
}
static Arena
make_arena(Base_Allocator *allocator, umem chunk_size){
    return(make_arena(allocator, chunk_size, 8));
}
static Arena
make_arena(Base_Allocator *allocator){
    return(make_arena(allocator, KB(16), 8));
}
static Cursor_Node*
arena__new_node(Arena *arena, umem min_size){
    min_size = clamp_bot(min_size, arena->chunk_size);
    Data memory = base_allocate(arena->base_allocator, min_size + sizeof(Cursor_Node));
    Cursor_Node *cursor_node = (Cursor_Node*)memory.data;
    cursor_node->cursor = make_cursor(cursor_node + 1, memory.size - sizeof(Cursor_Node));
    sll_stack_push(arena->cursor_node, cursor_node);
    return(cursor_node);
}
static Data
linalloc_push(Arena *arena, umem size){
    Data result = {};
    if (size > 0){
        Cursor_Node *cursor_node = arena->cursor_node;
        if (cursor_node == 0){
            cursor_node = arena__new_node(arena, size);
        }
        result = linalloc_push(&cursor_node->cursor, size);
        if (result.data == 0){
            cursor_node = arena__new_node(arena, size);
            result = linalloc_push(&cursor_node->cursor, size);
        }
        Data alignment_data = linalloc_align(&cursor_node->cursor, arena->alignment);
        result.size += alignment_data.size;
    }
    return(result);
}
static void
linalloc_pop(Arena *arena, umem size){
    Base_Allocator *allocator = arena->base_allocator;
    Cursor_Node *cursor_node = arena->cursor_node;
    for (Cursor_Node *prev = 0;
         cursor_node != 0 && size != 0;
         cursor_node = prev){
        prev = cursor_node->prev;
        if (size >= cursor_node->cursor.pos){
            size -= cursor_node->cursor.pos;
            base_free(allocator, cursor_node);
        }
        else{
            linalloc_pop(&cursor_node->cursor, size);
            break;
        }
    }
    arena->cursor_node = cursor_node;
}
static Data
linalloc_align(Arena *arena, umem alignment){
    arena->alignment = alignment;
    Data data = {};
    Cursor_Node *cursor_node = arena->cursor_node;
    if (cursor_node != 0){
        data = linalloc_align(&cursor_node->cursor, arena->alignment);
    }
    return(data);
}
static Temp_Memory_Arena
linalloc_begin_temp(Arena *arena){
    Cursor_Node *cursor_node = arena->cursor_node;
    Temp_Memory_Arena temp = {arena, cursor_node,
        cursor_node == 0?0:cursor_node->cursor.pos};
    return(temp);
}
static void
linalloc_end_temp(Temp_Memory_Arena temp){
    Base_Allocator *allocator = temp.arena->base_allocator;
    Cursor_Node *cursor_node = temp.arena->cursor_node;
    for (Cursor_Node *prev = 0;
         cursor_node != temp.cursor_node && cursor_node != 0;
         cursor_node = prev){
        prev = cursor_node->prev;
        base_free(allocator, cursor_node);
    }
    temp.arena->cursor_node = cursor_node;
    if (cursor_node != 0){
        if (temp.pos > 0){
            cursor_node->cursor.pos = temp.pos;
        }
        else{
            temp.arena->cursor_node = cursor_node->prev;
            base_free(allocator, cursor_node);
        }
    }
}
static void
linalloc_clear(Arena *arena){
    Temp_Memory_Arena temp = {arena, 0, 0};
    linalloc_end_temp(temp);
}
static void
arena_tap(Arena *arena){
    Cursor_Node *cursor_node = arena->cursor_node;
    if (cursor_node == 0){
        arena__new_node(arena, 0);
    }
    else if (cursor_node->cursor.pos == cursor_node->cursor.cap){
        arena__new_node(arena, 0);
    }
}
static Cursor*
arena_as_cursor(Arena *arena){
    Cursor *cursor = 0;
    arena_tap(arena);
    Cursor_Node *node = arena->cursor_node;
    if (node != 0){
        cursor = &node->cursor;
    }
    return(cursor);
}
static void*
linalloc_wrap_unintialized(Data data){
    return(data.data);
}
static void*
linalloc_wrap_zero(Data data){
    block_zero(data.data, data.size);
    return(data.data);
}
static void*
linalloc_wrap_write(Data data, umem size, void *src){
    block_copy(data.data, src, clamp_top(data.size, size));
    return(data.data);
}
#define push_array(a,T,c) ((T*)linalloc_wrap_unintialized(linalloc_push((a), sizeof(T)*(c))))
#define push_array_zero(a,T,c) ((T*)linalloc_wrap_zero(linalloc_push((a), sizeof(T)*(c))))
#define push_array_write(a,T,c,s) ((T*)linalloc_wrap_write(linalloc_push((a), sizeof(T)*(c)), sizeof(T)*(c), (s)))
#define pop_array(a,T,c) (linalloc_pop((a), sizeof(T)*(c)))
#define push_align(a,b) (linalloc_align((a), (b)))
#define push_align_zero(a,b) (linalloc_wrap_zero(linalloc_align((a), (b))))
static Temp_Memory
begin_temp(Cursor *cursor){
    Temp_Memory temp = {LinearAllocatorKind_Cursor};
    temp.temp_memory_cursor = linalloc_begin_temp(cursor);
    return(temp);
}
static Temp_Memory
begin_temp(Arena *arena){
    Temp_Memory temp = {LinearAllocatorKind_Arena};
    temp.temp_memory_arena = linalloc_begin_temp(arena);
    return(temp);
}
static void
end_temp(Temp_Memory temp){
    switch (temp.kind){
        case LinearAllocatorKind_Cursor:
        {
            linalloc_end_temp(temp.temp_memory_cursor);
        }break;
        case LinearAllocatorKind_Arena:
        {
            linalloc_end_temp(temp.temp_memory_arena);
        }break;
    }
}

////////////////////////////////

static Data
push_data(Arena *arena, umem size){
    Data result = {};
    result.data = push_array(arena, u8, size);
    result.size = size;
    return(result);
}

static Data
push_data_copy(Arena *arena, Data data){
    Data result = {};
    result.data = push_array_write(arena, u8, data.size, data.data);
    result.size = data.size;
    return(result);
}

static b32
data_match(Data a, Data b){
    return(a.size == b.size && block_match(a.data, b.data, a.size));
}

////////////////////////////////

static b32
character_is_slash(char c){
    return((c == '/') || (c == '\\'));
}
static b32
character_is_slash(u8 c){
    return((c == '/') || (c == '\\'));
}
static b32
character_is_slash(u16 c){
    return((c == '/') || (c == '\\'));
}
static b32
character_is_slash(u32 c){
    return((c == '/') || (c == '\\'));
}

static b32
character_is_upper(char c){
    return(('A' <= c) && (c <= 'Z'));
}
static b32
character_is_upper(u8 c){
    return(('A' <= c) && (c <= 'Z'));
}
static b32
character_is_upper(u16 c){
    return(('A' <= c) && (c <= 'Z'));
}
static b32
character_is_upper(u32 c){
    return(('A' <= c) && (c <= 'Z'));
}

static b32
character_is_lower(char c){
    return(('a' <= c) && (c <= 'z'));
}
static b32
character_is_lower(u8 c){
    return(('a' <= c) && (c <= 'z'));
}
static b32
character_is_lower(u16 c){
    return(('a' <= c) && (c <= 'z'));
}
static b32
character_is_lower(u32 c){
    return(('a' <= c) && (c <= 'z'));
}

static b32
character_is_lower_unicode(u8 c){
    return((('a' <= c) && (c <= 'z')) || c >= 128);
}
static b32
character_is_lower_unicode(u16 c){
    return((('a' <= c) && (c <= 'z')) || c >= 128);
}
static b32
character_is_lower_unicode(u32 c){
    return((('a' <= c) && (c <= 'z')) || c >= 128);
}

static char
character_to_upper(char c){
    if (('a' <= c) && (c <= 'z')){
        c -= 'a' - 'A';
    }
    return(c);
}
static u8
character_to_upper(u8 c){
    if (('a' <= c) && (c <= 'z')){
        c -= 'a' - 'A';
    }
    return(c);
}
static u16
character_to_upper(u16 c){
    if (('a' <= c) && (c <= 'z')){
        c -= 'a' - 'A';
    }
    return(c);
}
static u32
character_to_upper(u32 c){
    if (('a' <= c) && (c <= 'z')){
        c -= 'a' - 'A';
    }
    return(c);
}
static char
character_to_lower(char c){
    if (('A' <= c) && (c <= 'Z')){
        c += 'a' - 'A';
    }
    return(c);
}
static u8
character_to_lower(u8 c){
    if (('A' <= c) && (c <= 'Z')){
        c += 'a' - 'A';
    }
    return(c);
}
static u16
character_to_lower(u16 c){
    if (('A' <= c) && (c <= 'Z')){
        c += 'a' - 'A';
    }
    return(c);
}
static u32
character_to_lower(u32 c){
    if (('A' <= c) && (c <= 'Z')){
        c += 'a' - 'A';
    }
    return(c);
}

static b32
character_is_whitespace(char c){
    return(c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == '\f' || c == '\v');
}
static b32
character_is_whitespace(u8 c){
    return(c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == '\f' || c == '\v');
}
static b32
character_is_whitespace(u16 c){
    return(c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == '\f' || c == '\v');
}
static b32
character_is_whitespace(u32 c){
    return(c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == '\f' || c == '\v');
}

static b32
character_is_base10(char c){
    return('0' <= c && c <= '9');
}
static b32
character_is_base10(u8 c){
    return('0' <= c && c <= '9');
}
static b32
character_is_base10(u16 c){
    return('0' <= c && c <= '9');
}
static b32
character_is_base10(u32 c){
    return('0' <= c && c <= '9');
}

static b32
character_is_base16(char c){
    return(('0' <= c && c <= '9') || ('A' <= c && c <= 'F'));
}
static b32
character_is_base16(u8 c){
    return(('0' <= c && c <= '9') || ('A' <= c && c <= 'F'));
}
static b32
character_is_base16(u16 c){
    return(('0' <= c && c <= '9') || ('A' <= c && c <= 'F'));
}
static b32
character_is_base16(u32 c){
    return(('0' <= c && c <= '9') || ('A' <= c && c <= 'F'));
}

static b32
character_is_base64(char c){
    return(('0' <= c && c <= '9') ||
           ('a' <= c && c <= 'z') ||
           ('A' <= c && c <= 'Z') ||
           c == '_' || c == '$' || c == '?');
}
static b32
character_is_base64(u8 c){
    return(('0' <= c && c <= '9') ||
           ('a' <= c && c <= 'z') ||
           ('A' <= c && c <= 'Z') ||
           c == '_' || c == '$' || c == '?');
}
static b32
character_is_base64(u16 c){
    return(('0' <= c && c <= '9') ||
           ('a' <= c && c <= 'z') ||
           ('A' <= c && c <= 'Z') ||
           c == '_' || c == '$' || c == '?');
}
static b32
character_is_base64(u32 c){
    return(('0' <= c && c <= '9') ||
           ('a' <= c && c <= 'z') ||
           ('A' <= c && c <= 'Z') ||
           c == '_' || c == '$' || c == '?');
}

static b32
character_is_alpha(char c){
    return( (('a' <= c) && (c <= 'z')) || (('A' <= c) && (c <= 'Z')) || c == '_');
}
static b32
character_is_alpha(u8 c){
    return( (('a' <= c) && (c <= 'z')) || (('A' <= c) && (c <= 'Z')) || c == '_');
}
static b32
character_is_alpha(u16 c){
    return( (('a' <= c) && (c <= 'z')) || (('A' <= c) && (c <= 'Z')) || c == '_');
}
static b32
character_is_alpha(u32 c){
    return( (('a' <= c) && (c <= 'z')) || (('A' <= c) && (c <= 'Z')) || c == '_');
}

static b32
character_is_alpha_numeric(char c){
    return((('a' <= c) && (c <= 'z')) || (('A' <= c) && (c <= 'Z')) || (('0' <= c) && (c <= '9')) || c == '_');
}
static b32
character_is_alpha_numeric(u8 c){
    return((('a' <= c) && (c <= 'z')) || (('A' <= c) && (c <= 'Z')) || (('0' <= c) && (c <= '9')) || c == '_');
}
static b32
character_is_alpha_numeric(u16 c){
    return((('a' <= c) && (c <= 'z')) || (('A' <= c) && (c <= 'Z')) || (('0' <= c) && (c <= '9')) || c == '_');
}
static b32
character_is_alpha_numeric(u32 c){
    return((('a' <= c) && (c <= 'z')) || (('A' <= c) && (c <= 'Z')) || (('0' <= c) && (c <= '9')) || c == '_');
}


static b32
character_is_alpha_unicode(u8 c){
    return( (('a' <= c) && (c <= 'z')) || (('A' <= c) && (c <= 'Z')) || c == '_' || c >= 128);
}
static b32
character_is_alpha_unicode(u16 c){
    return( (('a' <= c) && (c <= 'z')) || (('A' <= c) && (c <= 'Z')) || c == '_' || c >= 128);
}
static b32
character_is_alpha_unicode(u32 c){
    return( (('a' <= c) && (c <= 'z')) || (('A' <= c) && (c <= 'Z')) || c == '_' || c >= 128);
}

static b32
character_is_alpha_numeric_unicode(u8 c){
    return((('a' <= c) && (c <= 'z')) || (('A' <= c) && (c <= 'Z')) || (('0' <= c) && (c <= '9')) || c == '_' || c >= 128);
}
static b32
character_is_alpha_numeric_unicode(u16 c){
    return((('a' <= c) && (c <= 'z')) || (('A' <= c) && (c <= 'Z')) || (('0' <= c) && (c <= '9')) || c == '_' || c >= 128);
}
static b32
character_is_alpha_numeric_unicode(u32 c){
    return((('a' <= c) && (c <= 'z')) || (('A' <= c) && (c <= 'Z')) || (('0' <= c) && (c <= '9')) || c == '_' || c >= 128);
}

static umem
cstring_length(char *str){
    umem length = 0;
    for (;str[length] != 0; length += 1);
    return(length);
}
static umem
cstring_length(u8 *str){
    umem length = 0;
    for (;str[length] != 0; length += 1);
    return(length);
}
static umem
cstring_length(u16 *str){
    umem length = 0;
    for (;str[length] != 0; length += 1);
    return(length);
}
static umem
cstring_length(u32 *str){
    umem length = 0;
    for (;str[length] != 0; length += 1);
    return(length);
}

static String_char
Schar(char *str, umem size, umem cap){
    String_char string = {str, size, cap};
    return(string);
}
static String_u8
Su8(u8 *str, umem size, umem cap){
    String_u8 string = {str, size, cap};
    return(string);
}
static String_u16
Su16(u16 *str, umem size, umem cap){
    String_u16 string = {str, size, cap};
    return(string);
}
static String_u32
Su32(u32 *str, umem size, umem cap){
    String_u32 string = {str, size, cap};
    return(string);
}

static String_Any
Sany(void *str, umem size, umem cap, String_Encoding encoding){
    String_Any string = {encoding};
    switch (encoding){
        case StringEncoding_ASCII: string.s_char = Schar((char*)str, size, cap); break;
        case StringEncoding_UTF8:  string.s_u8 = Su8((u8*)str, size, cap); break;
        case StringEncoding_UTF16: string.s_u16 = Su16((u16*)str, size, cap); break;
        case StringEncoding_UTF32: string.s_u32 = Su32((u32*)str, size, cap); break;
    }
    return(string);
}

static String_char
Schar(char *str, umem size){
    String_char string = {str, size, size + 1};
    return(string);
}
static String_u8
Su8(u8 *str, umem size){
    String_u8 string = {str, size, size + 1};
    return(string);
}
static String_u16
Su16(u16 *str, umem size){
    String_u16 string = {str, size, size + 1};
    return(string);
}
static String_u32
Su32(u32 *str, umem size){
    String_u32 string = {str, size, size + 1};
    return(string);
}

static String_Any
Sany(void *str, umem size, String_Encoding encoding){
    String_Any string = {encoding};
    switch (encoding){
        case StringEncoding_ASCII: string.s_char = Schar((char*)str, size); break;
        case StringEncoding_UTF8:  string.s_u8 = Su8((u8*)str, size); break;
        case StringEncoding_UTF16: string.s_u16 = Su16((u16*)str, size); break;
        case StringEncoding_UTF32: string.s_u32 = Su32((u32*)str, size); break;
    }
    return(string);
}

static String_char
Schar(char *str, char *one_past_last){
    return(Schar(str, (umem)(one_past_last - str)));
}
static String_u8
Su8(u8 *str, u8 *one_past_last){
    return(Su8(str, (umem)(one_past_last - str)));
}
static String_u16
Su16(u16 *str, u16 *one_past_last){
    return(Su16(str, (umem)(one_past_last - str)));
}
static String_u32
Su32(u32 *str, u32 *one_past_last){
    return(Su32(str, (umem)(one_past_last - str)));
}

static String_Any
Sany(void *str, void *one_past_last, String_Encoding encoding){
    String_Any string = {encoding};
    switch (encoding){
        case StringEncoding_ASCII: string.s_char = Schar((char*)str, (char*)one_past_last); break;
        case StringEncoding_UTF8:  string.s_u8 = Su8((u8*)str, (u8*)one_past_last); break;
        case StringEncoding_UTF16: string.s_u16 = Su16((u16*)str, (u16*)one_past_last); break;
        case StringEncoding_UTF32: string.s_u32 = Su32((u32*)str, (u32*)one_past_last); break;
    }
    return(string);
}

static String_char
Schar(char *str){
    umem size = cstring_length(str);
    String_char string = {str, size, size + 1};
    return(string);
}
static String_u8
Su8(u8 *str){
    umem size = cstring_length(str);
    String_u8 string = {str, size, size + 1};
    return(string);
}
static String_u16
Su16(u16 *str){
    umem size = cstring_length(str);
    String_u16 string = {str, size, size + 1};
    return(string);
}
static String_u32
Su32(u32 *str){
    umem size = cstring_length(str);
    String_u32 string = {str, size, size + 1};
    return(string);
}

static String_Any
Sany(void *str, String_Encoding encoding){
    String_Any string = {encoding};
    switch (encoding){
        case StringEncoding_ASCII: string.s_char = Schar((char*)str); break;
        case StringEncoding_UTF8:  string.s_u8 = Su8((u8*)str); break;
        case StringEncoding_UTF16: string.s_u16 = Su16((u16*)str); break;
        case StringEncoding_UTF32: string.s_u32 = Su32((u32*)str); break;
    }
    return(string);
}

static String_char
Schar(String_Const_char str, umem cap){
    String_char string = {str.str, str.size, cap};
    return(string);
}
static String_u8
Su8(String_Const_u8 str, umem cap){
    String_u8 string = {str.str, str.size, cap};
    return(string);
}
static String_u16
Su16(String_Const_u16 str, umem cap){
    String_u16 string = {str.str, str.size, cap};
    return(string);
}
static String_u32
Su32(String_Const_u32 str, umem cap){
    String_u32 string = {str.str, str.size, cap};
    return(string);
}

static String_Any
SCany(String_char str){
    String_Any string = {StringEncoding_ASCII};
    string.s_char = str;
    return(string);
}
static String_Any
SCany(String_u8 str){
    String_Any string = {StringEncoding_UTF8};
    string.s_u8 = str;
    return(string);
}
static String_Any
SCany(String_u16 str){
    String_Any string = {StringEncoding_UTF16};
    string.s_u16 = str;
    return(string);
}
static String_Any
SCany(String_u32 str){
    String_Any string = {StringEncoding_UTF32};
    string.s_u32 = str;
    return(string);
}

static String_Const_char
SCchar(char *str, umem size){
    String_Const_char string = {str, size};
    return(string);
}
static String_Const_u8
SCu8(u8 *str, umem size){
    String_Const_u8 string = {str, size};
    return(string);
}
static String_Const_u16
SCu16(u16 *str, umem size){
    String_Const_u16 string = {str, size};
    return(string);
}
static String_Const_u32
SCu32(u32 *str, umem size){
    String_Const_u32 string = {str, size};
    return(string);
}

static String_Const_Any
SCany(void *str, umem size, String_Encoding encoding){
    String_Const_Any string = {encoding};
    switch (encoding){
        case StringEncoding_ASCII: string.s_char = SCchar((char*)str, size); break;
        case StringEncoding_UTF8:  string.s_u8 = SCu8((u8*)str, size); break;
        case StringEncoding_UTF16: string.s_u16 = SCu16((u16*)str, size); break;
        case StringEncoding_UTF32: string.s_u32 = SCu32((u32*)str, size); break;
    }
    return(string);
}

static String_Const_char
SCchar(void){
    String_Const_char string = {};
    return(string);
}
static String_Const_u8
SCu8(void){
    String_Const_u8 string = {};
    return(string);
}
static String_Const_u16
SCu16(void){
    String_Const_u16 string = {};
    return(string);
}
static String_Const_u32
SCu32(void){
    String_Const_u32 string = {};
    return(string);
}

static String_Const_char
SCchar(char *str, char *one_past_last){
    return(SCchar(str, (umem)(one_past_last - str)));
}
static String_Const_u8
SCu8(u8 *str, u8 *one_past_last){
    return(SCu8(str, (umem)(one_past_last - str)));
}
static String_Const_u16
SCu16(u16 *str, u16 *one_past_last){
    return(SCu16(str, (umem)(one_past_last - str)));
}
static String_Const_u32
SCu32(u32 *str, u32 *one_past_last){
    return(SCu32(str, (umem)(one_past_last - str)));
}

static String_Const_Any
SCany(void *str, void *one_past_last, String_Encoding encoding){
    String_Const_Any string = {encoding};
    switch (encoding){
        case StringEncoding_ASCII: string.s_char = SCchar((char*)str, (char*)one_past_last); break;
        case StringEncoding_UTF8:  string.s_u8 = SCu8((u8*)str, (u8*)one_past_last); break;
        case StringEncoding_UTF16: string.s_u16 = SCu16((u16*)str, (u16*)one_past_last); break;
        case StringEncoding_UTF32: string.s_u32 = SCu32((u32*)str, (u32*)one_past_last); break;
    }
    return(string);
}

static String_Const_char
SCchar(char *str){
    umem size = cstring_length(str);
    String_Const_char string = {str, size};
    return(string);
}
static String_Const_u8
SCu8(u8 *str){
    umem size = cstring_length(str);
    String_Const_u8 string = {str, size};
    return(string);
}
static String_Const_u16
SCu16(u16 *str){
    umem size = cstring_length(str);
    String_Const_u16 string = {str, size};
    return(string);
}
static String_Const_u32
SCu32(u32 *str){
    umem size = cstring_length(str);
    String_Const_u32 string = {str, size};
    return(string);
}

static String_Const_char
SCchar(String_Const_u8 str){
    return(SCchar((char*)str.str, str.size));
}
static String_Const_u8
SCu8(String_Const_char str){
    return(SCu8((u8*)str.str, str.size));
}

static String_Const_u8
SCu8(char *str, umem length){
    return(SCu8((u8*)str, length));
}
static String_Const_u8
SCu8(char *first, char *one_past_last){
    return(SCu8((u8*)first, (u8*)one_past_last));
}
static String_Const_u8
SCu8(char *str){
    return(SCu8((u8*)str));
}

static String_Const_u8
SCu8(Data data){
    return(SCu8((u8*)data.data, data.size));
}

static String_Const_u16
SCu16(wchar_t *str, umem size){
    return(SCu16((u16*)str, size));
}
static String_Const_u16
SCu16(wchar_t *str){
    return(SCu16((u16*)str));
}

static String_Const_Any
SCany(void *str, String_Encoding encoding){
    String_Const_Any string = {encoding};
    switch (encoding){
        case StringEncoding_ASCII: string.s_char = SCchar((char*)str); break;
        case StringEncoding_UTF8:  string.s_u8 = SCu8((u8*)str); break;
        case StringEncoding_UTF16: string.s_u16 = SCu16((u16*)str); break;
        case StringEncoding_UTF32: string.s_u32 = SCu32((u32*)str); break;
    }
    return(string);
}

static String_Const_Any
SCany(String_Const_char str){
    String_Const_Any string = {StringEncoding_ASCII};
    string.s_char = str;
    return(string);
}
static String_Const_Any
SCany(String_Const_u8 str){
    String_Const_Any string = {StringEncoding_UTF8};
    string.s_u8 = str;
    return(string);
}
static String_Const_Any
SCany(String_Const_u16 str){
    String_Const_Any string = {StringEncoding_UTF16};
    string.s_u16 = str;
    return(string);
}
static String_Const_Any
SCany(String_Const_u32 str){
    String_Const_Any string = {StringEncoding_UTF32};
    string.s_u32 = str;
    return(string);
}

#define string_litexpr(s) SCchar((s), sizeof(s) - 1)
#define string_litinit(s) {(s), sizeof(s) - 1}
#define string_u8_litexpr(s) SCu8((u8*)(s), sizeof(s) - 1)
#define string_u8_litinit(s) {(u8*)(s), sizeof(s) - 1}

#define string_expand(s) (i32)(s).size, (char*)(s).str

static char
string_get_character(String_Const_char str, umem i){
    char r = 0;
    if (i < str.size){
        r = str.str[i];
    }
    return(r);
}
static u8
string_get_character(String_Const_u8 str, umem i){
    u8 r = 0;
    if (i < str.size){
        r = str.str[i];
    }
    return(r);
}
static u16
string_get_character(String_Const_u16 str, umem i){
    u16 r = 0;
    if (i < str.size){
        r = str.str[i];
    }
    return(r);
}
static u32
string_get_character(String_Const_u32 str, umem i){
    u32 r = 0;
    if (i < str.size){
        r = str.str[i];
    }
    return(r);
}

static String_Const_char
string_prefix(String_Const_char str, umem size){
    size = clamp_top(size, str.size);
    str.size = size;
    return(str);
}
static String_Const_u8
string_prefix(String_Const_u8 str, umem size){
    size = clamp_top(size, str.size);
    str.size = size;
    return(str);
}
static String_Const_u16
string_prefix(String_Const_u16 str, umem size){
    size = clamp_top(size, str.size);
    str.size = size;
    return(str);
}
static String_Const_u32
string_prefix(String_Const_u32 str, umem size){
    size = clamp_top(size, str.size);
    str.size = size;
    return(str);
}

static String_Const_Any
string_prefix(String_Const_Any str, umem size){
    switch (str.encoding){
        case StringEncoding_ASCII: str.s_char = string_prefix(str.s_char, size); break;
        case StringEncoding_UTF8:  str.s_u8   = string_prefix(str.s_u8  , size); break;
        case StringEncoding_UTF16: str.s_u16  = string_prefix(str.s_u16 , size); break;
        case StringEncoding_UTF32: str.s_u32  = string_prefix(str.s_u32 , size); break;
    }
    return(str);
}

static String_Const_char
string_postfix(String_Const_char str, umem size){
    size = clamp_top(size, str.size);
    str.str += (str.size - size);
    str.size = size;
    return(str);
}
static String_Const_u8
string_postfix(String_Const_u8 str, umem size){
    size = clamp_top(size, str.size);
    str.str += (str.size - size);
    str.size = size;
    return(str);
}
static String_Const_u16
string_postfix(String_Const_u16 str, umem size){
    size = clamp_top(size, str.size);
    str.str += (str.size - size);
    str.size = size;
    return(str);
}
static String_Const_u32
string_postfix(String_Const_u32 str, umem size){
    size = clamp_top(size, str.size);
    str.str += (str.size - size);
    str.size = size;
    return(str);
}

static String_Const_Any
string_postfix(String_Const_Any str, umem size){
    switch (str.encoding){
        case StringEncoding_ASCII: str.s_char = string_postfix(str.s_char, size); break;
        case StringEncoding_UTF8:  str.s_u8   = string_postfix(str.s_u8  , size); break;
        case StringEncoding_UTF16: str.s_u16  = string_postfix(str.s_u16 , size); break;
        case StringEncoding_UTF32: str.s_u32  = string_postfix(str.s_u32 , size); break;
    }
    return(str);
}

static String_Const_char
string_skip(String_Const_char str, umem n){
    n = clamp_top(n, str.size);
    str.str += n;;
    str.size -= n;
    return(str);
}
static String_Const_u8
string_skip(String_Const_u8 str, umem n){
    n = clamp_top(n, str.size);
    str.str += n;;
    str.size -= n;
    return(str);
}
static String_Const_u16
string_skip(String_Const_u16 str, umem n){
    n = clamp_top(n, str.size);
    str.str += n;;
    str.size -= n;
    return(str);
}
static String_Const_u32
string_skip(String_Const_u32 str, umem n){
    n = clamp_top(n, str.size);
    str.str += n;;
    str.size -= n;
    return(str);
}

static String_Const_Any
string_skip(String_Const_Any str, umem n){
    switch (str.encoding){
        case StringEncoding_ASCII: str.s_char = string_skip(str.s_char, n); break;
        case StringEncoding_UTF8:  str.s_u8   = string_skip(str.s_u8  , n); break;
        case StringEncoding_UTF16: str.s_u16  = string_skip(str.s_u16 , n); break;
        case StringEncoding_UTF32: str.s_u32  = string_skip(str.s_u32 , n); break;
    }
    return(str);
}

static String_Const_char
string_chop(String_Const_char str, umem n){
    n = clamp_top(n, str.size);
    str.size -= n;
    return(str);
}
static String_Const_u8
string_chop(String_Const_u8 str, umem n){
    n = clamp_top(n, str.size);
    str.size -= n;
    return(str);
}
static String_Const_u16
string_chop(String_Const_u16 str, umem n){
    n = clamp_top(n, str.size);
    str.size -= n;
    return(str);
}
static String_Const_u32
string_chop(String_Const_u32 str, umem n){
    n = clamp_top(n, str.size);
    str.size -= n;
    return(str);
}

static String_Const_Any
string_chop(String_Const_Any str, umem n){
    switch (str.encoding){
        case StringEncoding_ASCII: str.s_char = string_chop(str.s_char, n); break;
        case StringEncoding_UTF8:  str.s_u8   = string_chop(str.s_u8  , n); break;
        case StringEncoding_UTF16: str.s_u16  = string_chop(str.s_u16 , n); break;
        case StringEncoding_UTF32: str.s_u32  = string_chop(str.s_u32 , n); break;
    }
    return(str);
}

static umem
string_find_first(String_Const_char str, char c){
    umem i = 0;
    for (;i < str.size && c != str.str[i]; i += 1);
    return(i);
}
static umem
string_find_first(String_Const_u8 str, u8 c){
    umem i = 0;
    for (;i < str.size && c != str.str[i]; i += 1);
    return(i);
}
static umem
string_find_first(String_Const_u16 str, u16 c){
    umem i = 0;
    for (;i < str.size && c != str.str[i]; i += 1);
    return(i);
}
static umem
string_find_first(String_Const_u32 str, u32 c){
    umem i = 0;
    for (;i < str.size && c != str.str[i]; i += 1);
    return(i);
}

static imem
string_find_last(String_Const_char str, char c){
    imem size = (imem)str.size;
    imem i = size - 1;
    for (;i >= 0 && c != str.str[i]; i -= 1);
    return(i);
}
static imem
string_find_last(String_Const_u8 str, u8 c){
    imem size = (imem)str.size;
    imem i = size - 1;
    for (;i >= 0 && c != str.str[i]; i -= 1);
    return(i);
}
static imem
string_find_last(String_Const_u16 str, u16 c){
    imem size = (imem)str.size;
    imem i = size - 1;
    for (;i >= 0 && c != str.str[i]; i -= 1);
    return(i);
}
static imem
string_find_last(String_Const_u32 str, u32 c){
    imem size = (imem)str.size;
    imem i = size - 1;
    for (;i >= 0 && c != str.str[i]; i -= 1);
    return(i);
}

static umem
string_find_first_non_whitespace(String_Const_char str){
    umem i = 0;
    for (;i < str.size && character_is_whitespace(str.str[i]); i += 1);
    return(i);
}
static umem
string_find_first_non_whitespace(String_Const_u8 str){
    umem i = 0;
    for (;i < str.size && character_is_whitespace(str.str[i]); i += 1);
    return(i);
}
static umem
string_find_first_non_whitespace(String_Const_u16 str){
    umem i = 0;
    for (;i < str.size && character_is_whitespace(str.str[i]); i += 1);
    return(i);
}
static umem
string_find_first_non_whitespace(String_Const_u32 str){
    umem i = 0;
    for (;i < str.size && character_is_whitespace(str.str[i]); i += 1);
    return(i);
}
static imem
string_find_last_non_whitespace(String_Const_char str){
    imem size = (imem)str.size;
    imem i = size - 1;
    for (;i >= 0 && character_is_whitespace(str.str[i]); i -= 1);
    return(i);
}
static imem
string_find_last_non_whitespace(String_Const_u8 str){
    imem size = (imem)str.size;
    imem i = size - 1;
    for (;i >= 0 && character_is_whitespace(str.str[i]); i -= 1);
    return(i);
}
static imem
string_find_last_non_whitespace(String_Const_u16 str){
    imem size = (imem)str.size;
    imem i = size - 1;
    for (;i >= 0 && character_is_whitespace(str.str[i]); i -= 1);
    return(i);
}
static imem
string_find_last_non_whitespace(String_Const_u32 str){
    imem size = (imem)str.size;
    imem i = size - 1;
    for (;i >= 0 && character_is_whitespace(str.str[i]); i -= 1);
    return(i);
}

static umem
string_find_first_slash(String_Const_char str){
    umem i = 0;
    for (;i < str.size && !character_is_slash(str.str[i]); i += 1);
    return(i);
}
static umem
string_find_first_slash(String_Const_u8 str){
    umem i = 0;
    for (;i < str.size && !character_is_slash(str.str[i]); i += 1);
    return(i);
}
static umem
string_find_first_slash(String_Const_u16 str){
    umem i = 0;
    for (;i < str.size && !character_is_slash(str.str[i]); i += 1);
    return(i);
}
static umem
string_find_first_slash(String_Const_u32 str){
    umem i = 0;
    for (;i < str.size && !character_is_slash(str.str[i]); i += 1);
    return(i);
}
static imem
string_find_last_slash(String_Const_char str){
    imem size = (imem)str.size;
    imem i = size - 1;
    for (;i >= 0 && !character_is_slash(str.str[i]); i -= 1);
    return(i);
}
static imem
string_find_last_slash(String_Const_u8 str){
    imem size = (imem)str.size;
    imem i = size - 1;
    for (;i >= 0 && !character_is_slash(str.str[i]); i -= 1);
    return(i);
}
static imem
string_find_last_slash(String_Const_u16 str){
    imem size = (imem)str.size;
    imem i = size - 1;
    for (;i >= 0 && !character_is_slash(str.str[i]); i -= 1);
    return(i);
}
static imem
string_find_last_slash(String_Const_u32 str){
    imem size = (imem)str.size;
    imem i = size - 1;
    for (;i >= 0 && !character_is_slash(str.str[i]); i -= 1);
    return(i);
}

static String_Const_char
string_remove_last_folder(String_Const_char str){
    if (str.size > 0){
        str.size -= 1;
    }
    imem slash_pos = string_find_last_slash(str);
    if (slash_pos < 0){
        str.size = 0;
    }
    else{
        str.size = slash_pos + 1;
    }
    return(str);
}
static String_Const_u8
string_remove_last_folder(String_Const_u8 str){
    if (str.size > 0){
        str.size -= 1;
    }
    imem slash_pos = string_find_last_slash(str);
    if (slash_pos < 0){
        str.size = 0;
    }
    else{
        str.size = slash_pos + 1;
    }
    return(str);
}
static String_Const_u16
string_remove_last_folder(String_Const_u16 str){
    if (str.size > 0){
        str.size -= 1;
    }
    imem slash_pos = string_find_last_slash(str);
    if (slash_pos < 0){
        str.size = 0;
    }
    else{
        str.size = slash_pos + 1;
    }
    return(str);
}
static String_Const_u32
string_remove_last_folder(String_Const_u32 str){
    if (str.size > 0){
        str.size -= 1;
    }
    imem slash_pos = string_find_last_slash(str);
    if (slash_pos < 0){
        str.size = 0;
    }
    else{
        str.size = slash_pos + 1;
    }
    return(str);
}

static String_Const_char
string_front_of_path(String_Const_char str){
    imem slash_pos = string_find_last_slash(str);
    if (slash_pos >= 0){
        str = string_skip(str, slash_pos + 1);
    }
    return(str);
}
static String_Const_u8
string_front_of_path(String_Const_u8 str){
    imem slash_pos = string_find_last_slash(str);
    if (slash_pos >= 0){
        str = string_skip(str, slash_pos + 1);
    }
    return(str);
}
static String_Const_u16
string_front_of_path(String_Const_u16 str){
    imem slash_pos = string_find_last_slash(str);
    if (slash_pos >= 0){
        str = string_skip(str, slash_pos + 1);
    }
    return(str);
}
static String_Const_u32
string_front_of_path(String_Const_u32 str){
    imem slash_pos = string_find_last_slash(str);
    if (slash_pos >= 0){
        str = string_skip(str, slash_pos + 1);
    }
    return(str);
}

static String_Const_char
string_file_extension(String_Const_char string){
    return(string_skip(string, string_find_last(string, '.') + 1));
}
static String_Const_u8
string_file_extension(String_Const_u8 string){
    return(string_skip(string, string_find_last(string, '.') + 1));
}
static String_Const_u16
string_file_extension(String_Const_u16 string){
    return(string_skip(string, string_find_last(string, '.') + 1));
}
static String_Const_u32
string_file_extension(String_Const_u32 string){
    return(string_skip(string, string_find_last(string, '.') + 1));
}

static String_Const_char
string_file_without_extension(String_Const_char string){
    imem pos = string_find_last(string, '.');
    if (pos > 0){
        string = string_prefix(string, pos);
    }
    return(string);
}
static String_Const_u8
string_file_without_extension(String_Const_u8 string){
    imem pos = string_find_last(string, '.');
    if (pos > 0){
        string = string_prefix(string, pos);
    }
    return(string);
}
static String_Const_u16
string_file_without_extension(String_Const_u16 string){
    imem pos = string_find_last(string, '.');
    if (pos > 0){
        string = string_prefix(string, pos);
    }
    return(string);
}
static String_Const_u32
string_file_without_extension(String_Const_u32 string){
    imem pos = string_find_last(string, '.');
    if (pos > 0){
        string = string_prefix(string, pos);
    }
    return(string);
}

static String_Const_char
string_skip_whitespace(String_Const_char str){
    umem f = string_find_first_non_whitespace(str);
    str = string_skip(str, f);
    return(str);
}
static String_Const_u8
string_skip_whitespace(String_Const_u8 str){
    umem f = string_find_first_non_whitespace(str);
    str = string_skip(str, f);
    return(str);
}
static String_Const_u16
string_skip_whitespace(String_Const_u16 str){
    umem f = string_find_first_non_whitespace(str);
    str = string_skip(str, f);
    return(str);
}
static String_Const_u32
string_skip_whitespace(String_Const_u32 str){
    umem f = string_find_first_non_whitespace(str);
    str = string_skip(str, f);
    return(str);
}

static String_Const_char
string_chop_whitespace(String_Const_char str){
    imem e = string_find_last_non_whitespace(str);
    str = string_prefix(str, (umem)(e + 1));
    return(str);
}
static String_Const_u8
string_chop_whitespace(String_Const_u8 str){
    imem e = string_find_last_non_whitespace(str);
    str = string_prefix(str, (umem)(e + 1));
    return(str);
}
static String_Const_u16
string_chop_whitespace(String_Const_u16 str){
    imem e = string_find_last_non_whitespace(str);
    str = string_prefix(str, (umem)(e + 1));
    return(str);
}
static String_Const_u32
string_chop_whitespace(String_Const_u32 str){
    imem e = string_find_last_non_whitespace(str);
    str = string_prefix(str, (umem)(e + 1));
    return(str);
}

static String_Const_char
string_skip_chop_whitespace(String_Const_char str){
    umem f = string_find_first_non_whitespace(str);
    str = string_skip(str, f);
    imem e = string_find_last_non_whitespace(str);
    str = string_prefix(str, (umem)(e + 1));
    return(str);
}
static String_Const_u8
string_skip_chop_whitespace(String_Const_u8 str){
    umem f = string_find_first_non_whitespace(str);
    str = string_skip(str, f);
    imem e = string_find_last_non_whitespace(str);
    str = string_prefix(str, (umem)(e + 1));
    return(str);
}
static String_Const_u16
string_skip_chop_whitespace(String_Const_u16 str){
    umem f = string_find_first_non_whitespace(str);
    str = string_skip(str, f);
    imem e = string_find_last_non_whitespace(str);
    str = string_prefix(str, (umem)(e + 1));
    return(str);
}
static String_Const_u32
string_skip_chop_whitespace(String_Const_u32 str){
    umem f = string_find_first_non_whitespace(str);
    str = string_skip(str, f);
    imem e = string_find_last_non_whitespace(str);
    str = string_prefix(str, (umem)(e + 1));
    return(str);
}

static b32
string_match(String_Const_char a, String_Const_char b){
    b32 result = false;
    if (a.size == b.size){
        result = true;
        for (umem i = 0; i < a.size; i += 1){
            if (a.str[i] != b.str[i]){
                result = false;
                break;
            }
        }
    }
    return(result);
}
static b32
string_match(String_Const_u8 a, String_Const_u8 b){
    b32 result = false;
    if (a.size == b.size){
        result = true;
        for (umem i = 0; i < a.size; i += 1){
            if (a.str[i] != b.str[i]){
                result = false;
                break;
            }
        }
    }
    return(result);
}
static b32
string_match(String_Const_u16 a, String_Const_u16 b){
    b32 result = false;
    if (a.size == b.size){
        result = true;
        for (umem i = 0; i < a.size; i += 1){
            if (a.str[i] != b.str[i]){
                result = false;
                break;
            }
        }
    }
    return(result);
}
static b32
string_match(String_Const_u32 a, String_Const_u32 b){
    b32 result = false;
    if (a.size == b.size){
        result = true;
        for (umem i = 0; i < a.size; i += 1){
            if (a.str[i] != b.str[i]){
                result = false;
                break;
            }
        }
    }
    return(result);
}

static b32
string_match(String_Const_Any a, String_Const_Any b){
    b32 result = false;
    if (a.encoding == b.encoding){
        switch (a.encoding){
            case StringEncoding_ASCII: result = string_match(a.s_char, b.s_char); break;
            case StringEncoding_UTF8:  result = string_match(a.s_u8  , b.s_u8  ); break;
            case StringEncoding_UTF16: result = string_match(a.s_u16 , b.s_u16 ); break;
            case StringEncoding_UTF32: result = string_match(a.s_u32 , b.s_u32 ); break;
        }
    }
    return(result);
}

static b32
string_match_insensitive(String_Const_char a, String_Const_char b){
    b32 result = false;
    if (a.size == b.size){
        result = true;
        for (umem i = 0; i < a.size; i += 1){
            if (character_to_upper(a.str[i]) != character_to_upper(b.str[i])){
                result = false;
                break;
            }
        }
    }
    return(result);
}
static b32
string_match_insensitive(String_Const_u8 a, String_Const_u8 b){
    b32 result = false;
    if (a.size == b.size){
        result = true;
        for (umem i = 0; i < a.size; i += 1){
            if (character_to_upper(a.str[i]) != character_to_upper(b.str[i])){
                result = false;
                break;
            }
        }
    }
    return(result);
}
static b32
string_match_insensitive(String_Const_u16 a, String_Const_u16 b){
    b32 result = false;
    if (a.size == b.size){
        result = true;
        for (umem i = 0; i < a.size; i += 1){
            if (character_to_upper(a.str[i]) != character_to_upper(b.str[i])){
                result = false;
                break;
            }
        }
    }
    return(result);
}
static b32
string_match_insensitive(String_Const_u32 a, String_Const_u32 b){
    b32 result = false;
    if (a.size == b.size){
        result = true;
        for (umem i = 0; i < a.size; i += 1){
            if (character_to_upper(a.str[i]) != character_to_upper(b.str[i])){
                result = false;
                break;
            }
        }
    }
    return(result);
}

static b32
string_match(String_Const_char a, String_Const_char b, String_Match_Rule rule){
    b32 result = false;
    switch (rule){
        case StringMatch_Exact:
        {
            result = string_match(a, b);
        }break;
        case StringMatch_CaseInsensitive:
        {
            result = string_match_insensitive(a, b);
        }break;
    }
    return(result);
}
static b32
string_match(String_Const_u8 a, String_Const_u8 b, String_Match_Rule rule){
    b32 result = false;
    switch (rule){
        case StringMatch_Exact:
        {
            result = string_match(a, b);
        }break;
        case StringMatch_CaseInsensitive:
        {
            result = string_match_insensitive(a, b);
        }break;
    }
    return(result);
}
static b32
string_match(String_Const_u16 a, String_Const_u16 b, String_Match_Rule rule){
    b32 result = false;
    switch (rule){
        case StringMatch_Exact:
        {
            result = string_match(a, b);
        }break;
        case StringMatch_CaseInsensitive:
        {
            result = string_match_insensitive(a, b);
        }break;
    }
    return(result);
}
static b32
string_match(String_Const_u32 a, String_Const_u32 b, String_Match_Rule rule){
    b32 result = false;
    switch (rule){
        case StringMatch_Exact:
        {
            result = string_match(a, b);
        }break;
        case StringMatch_CaseInsensitive:
        {
            result = string_match_insensitive(a, b);
        }break;
    }
    return(result);
}

static umem
string_find_first(String_Const_char str, String_Const_char needle, String_Match_Rule rule){
    umem i = 0;
    if (needle.size > 0){
        i = str.size;
        if (str.size >= needle.size){
			i = 0;
            umem one_past_last = str.size - needle.size + 1;
            for (;i < one_past_last; i += 1){
                if (str.str[i] == needle.str[0]){
                    String_Const_char source_part = string_prefix(string_skip(str, i), needle.size);
                    if (string_match(source_part, needle, rule)){
                        break;
                    }
                }
            }
            if (i == one_past_last){
                i = str.size;
            }
        }
    }
    return(i);
}
static umem
string_find_first(String_Const_u8 str, String_Const_u8 needle, String_Match_Rule rule){
    umem i = 0;
    if (needle.size > 0){
        i = str.size;
        if (str.size >= needle.size){
			i = 0;
            umem one_past_last = str.size - needle.size + 1;
            for (;i < one_past_last; i += 1){
                if (str.str[i] == needle.str[0]){
                    String_Const_u8 source_part = string_prefix(string_skip(str, i), needle.size);
                    if (string_match(source_part, needle, rule)){
                        break;
                    }
                }
            }
            if (i == one_past_last){
                i = str.size;
            }
        }
    }
    return(i);
}
static umem
string_find_first(String_Const_u16 str, String_Const_u16 needle, String_Match_Rule rule){
    umem i = 0;
    if (needle.size > 0){
        i = str.size;
        if (str.size >= needle.size){
			i = 0;
            umem one_past_last = str.size - needle.size + 1;
            for (;i < one_past_last; i += 1){
                if (str.str[i] == needle.str[0]){
                    String_Const_u16 source_part = string_prefix(string_skip(str, i), needle.size);
                    if (string_match(source_part, needle, rule)){
                        break;
                    }
                }
            }
            if (i == one_past_last){
                i = str.size;
            }
        }
    }
    return(i);
}
static umem
string_find_first(String_Const_u32 str, String_Const_u32 needle, String_Match_Rule rule){
    umem i = 0;
    if (needle.size > 0){
        i = str.size;
        if (str.size >= needle.size){
			i = 0;
            umem one_past_last = str.size - needle.size + 1;
            for (;i < one_past_last; i += 1){
                if (str.str[i] == needle.str[0]){
                    String_Const_u32 source_part = string_prefix(string_skip(str, i), needle.size);
                    if (string_match(source_part, needle, rule)){
                        break;
                    }
                }
            }
            if (i == one_past_last){
                i = str.size;
            }
        }
    }
    return(i);
}

static umem
string_find_first(String_Const_char str, String_Const_char needle){
    return(string_find_first(str, needle, StringMatch_Exact));
}
static umem
string_find_first(String_Const_u8 str, String_Const_u8 needle){
    return(string_find_first(str, needle, StringMatch_Exact));
}
static umem
string_find_first(String_Const_u16 str, String_Const_u16 needle){
    return(string_find_first(str, needle, StringMatch_Exact));
}
static umem
string_find_first(String_Const_u32 str, String_Const_u32 needle){
    return(string_find_first(str, needle, StringMatch_Exact));
}
static umem
string_find_first_insensitive(String_Const_char str, String_Const_char needle){
    return(string_find_first(str, needle, StringMatch_CaseInsensitive));
}
static umem
string_find_first_insensitive(String_Const_u8 str, String_Const_u8 needle){
    return(string_find_first(str, needle, StringMatch_CaseInsensitive));
}
static umem
string_find_first_insensitive(String_Const_u16 str, String_Const_u16 needle){
    return(string_find_first(str, needle, StringMatch_CaseInsensitive));
}
static umem
string_find_first_insensitive(String_Const_u32 str, String_Const_u32 needle){
    return(string_find_first(str, needle, StringMatch_CaseInsensitive));
}

static i32
string_compare(String_Const_char a, String_Const_char b){
    i32 result = 0;
    for (umem i = 0; i < a.size || i < b.size; i += 1){
        char ca = (i < a.size)?0:a.str[i];
        char cb = (i < b.size)?0:b.str[i];
        i32 dif = (ca) != (cb);
        if (dif != 0){
            result = (dif > 0)?1:-1;
            break;
        }
    }
    return(result);
}
static i32
string_compare(String_Const_u8 a, String_Const_u8 b){
    i32 result = 0;
    for (umem i = 0; i < a.size || i < b.size; i += 1){
        u8 ca = (i < a.size)?0:a.str[i];
        u8 cb = (i < b.size)?0:b.str[i];
        i32 dif = (ca) != (cb);
        if (dif != 0){
            result = (dif > 0)?1:-1;
            break;
        }
    }
    return(result);
}
static i32
string_compare(String_Const_u16 a, String_Const_u16 b){
    i32 result = 0;
    for (umem i = 0; i < a.size || i < b.size; i += 1){
        u16 ca = (i < a.size)?0:a.str[i];
        u16 cb = (i < b.size)?0:b.str[i];
        i32 dif = (ca) != (cb);
        if (dif != 0){
            result = (dif > 0)?1:-1;
            break;
        }
    }
    return(result);
}
static i32
string_compare(String_Const_u32 a, String_Const_u32 b){
    i32 result = 0;
    for (umem i = 0; i < a.size || i < b.size; i += 1){
        u32 ca = (i < a.size)?0:a.str[i];
        u32 cb = (i < b.size)?0:b.str[i];
        i32 dif = (ca) != (cb);
        if (dif != 0){
            result = (dif > 0)?1:-1;
            break;
        }
    }
    return(result);
}

static i32
string_compare_insensitive(String_Const_char a, String_Const_char b){
    i32 result = 0;
    for (umem i = 0; i < a.size || i < b.size; i += 1){
        char ca = (i <= a.size)?0:a.str[i];
        char cb = (i <= b.size)?0:b.str[i];
        i32 dif = character_to_upper(ca) - character_to_upper(cb);
        if (dif != 0){
            result = (dif > 0)?1:-1;
            break;
        }
    }
    return(result);
}
static i32
string_compare_insensitive(String_Const_u8 a, String_Const_u8 b){
    i32 result = 0;
    for (umem i = 0; i < a.size || i < b.size; i += 1){
        u8 ca = (i <= a.size)?0:a.str[i];
        u8 cb = (i <= b.size)?0:b.str[i];
        i32 dif = character_to_upper(ca) - character_to_upper(cb);
        if (dif != 0){
            result = (dif > 0)?1:-1;
            break;
        }
    }
    return(result);
}
static i32
string_compare_insensitive(String_Const_u16 a, String_Const_u16 b){
    i32 result = 0;
    for (umem i = 0; i < a.size || i < b.size; i += 1){
        u16 ca = (i <= a.size)?0:a.str[i];
        u16 cb = (i <= b.size)?0:b.str[i];
        i32 dif = character_to_upper(ca) - character_to_upper(cb);
        if (dif != 0){
            result = (dif > 0)?1:-1;
            break;
        }
    }
    return(result);
}
static i32
string_compare_insensitive(String_Const_u32 a, String_Const_u32 b){
    i32 result = 0;
    for (umem i = 0; i < a.size || i < b.size; i += 1){
        u32 ca = (i <= a.size)?0:a.str[i];
        u32 cb = (i <= b.size)?0:b.str[i];
        i32 dif = character_to_upper(ca) - character_to_upper(cb);
        if (dif != 0){
            result = (dif > 0)?1:-1;
            break;
        }
    }
    return(result);
}

static String_Const_char
string_mod_upper(String_Const_char str){
    for (umem i = 0; i < str.size; i += 1){
        str.str[i] = character_to_upper(str.str[i]);
    }
    return(str);
}
static String_Const_u8
string_mod_upper(String_Const_u8 str){
    for (umem i = 0; i < str.size; i += 1){
        str.str[i] = character_to_upper(str.str[i]);
    }
    return(str);
}
static String_Const_u16
string_mod_upper(String_Const_u16 str){
    for (umem i = 0; i < str.size; i += 1){
        str.str[i] = character_to_upper(str.str[i]);
    }
    return(str);
}
static String_Const_u32
string_mod_upper(String_Const_u32 str){
    for (umem i = 0; i < str.size; i += 1){
        str.str[i] = character_to_upper(str.str[i]);
    }
    return(str);
}
static String_Const_char
string_mod_lower(String_Const_char str){
    for (umem i = 0; i < str.size; i += 1){
        str.str[i] = character_to_lower(str.str[i]);
    }
    return(str);
}
static String_Const_u8
string_mod_lower(String_Const_u8 str){
    for (umem i = 0; i < str.size; i += 1){
        str.str[i] = character_to_lower(str.str[i]);
    }
    return(str);
}
static String_Const_u16
string_mod_lower(String_Const_u16 str){
    for (umem i = 0; i < str.size; i += 1){
        str.str[i] = character_to_lower(str.str[i]);
    }
    return(str);
}
static String_Const_u32
string_mod_lower(String_Const_u32 str){
    for (umem i = 0; i < str.size; i += 1){
        str.str[i] = character_to_lower(str.str[i]);
    }
    return(str);
}

static String_Const_char
string_mod_replace_character(String_Const_char str, char o, char n){
    for (umem i = 0; i < str.size; i += 1){
        char c = str.str[i];
        str.str[i] = (c == o)?(n):(c);
    }
    return(str);
}
static String_Const_u8
string_mod_replace_character(String_Const_u8 str, u8 o, u8 n){
    for (umem i = 0; i < str.size; i += 1){
        u8 c = str.str[i];
        str.str[i] = (c == o)?(n):(c);
    }
    return(str);
}
static String_Const_u16
string_mod_replace_character(String_Const_u16 str, u16 o, u16 n){
    for (umem i = 0; i < str.size; i += 1){
        u16 c = str.str[i];
        str.str[i] = (c == o)?(n):(c);
    }
    return(str);
}
static String_Const_u32
string_mod_replace_character(String_Const_u32 str, u32 o, u32 n){
    for (umem i = 0; i < str.size; i += 1){
        u32 c = str.str[i];
        str.str[i] = (c == o)?(n):(c);
    }
    return(str);
}

static b32
string_append(String_char *dst, String_Const_char src){
    b32 result = false;
    umem available = dst->cap - dst->size;
    if (src.size <= available){
        result = true;
    }
    umem copy_size = clamp_top(src.size, available);
    block_copy(dst->str + dst->size, src.str, copy_size);
    dst->size += copy_size;
    return(result);
}
static b32
string_append(String_u8 *dst, String_Const_u8 src){
    b32 result = false;
    umem available = dst->cap - dst->size;
    if (src.size <= available){
        result = true;
    }
    umem copy_size = clamp_top(src.size, available);
    block_copy(dst->str + dst->size, src.str, copy_size);
    dst->size += copy_size;
    return(result);
}
static b32
string_append(String_u16 *dst, String_Const_u16 src){
    b32 result = false;
    umem available = dst->cap - dst->size;
    if (src.size <= available){
        result = true;
    }
    umem copy_size = clamp_top(src.size, available);
    block_copy(dst->str + dst->size, src.str, copy_size);
    dst->size += copy_size;
    return(result);
}
static b32
string_append(String_u32 *dst, String_Const_u32 src){
    b32 result = false;
    umem available = dst->cap - dst->size;
    if (src.size <= available){
        result = true;
    }
    umem copy_size = clamp_top(src.size, available);
    block_copy(dst->str + dst->size, src.str, copy_size);
    dst->size += copy_size;
    return(result);
}

static b32
string_append_character(String_char *dst, char c){
    return(string_append(dst, SCchar(&c, 1)));
}
static b32
string_append_character(String_u8 *dst, u8 c){
    return(string_append(dst, SCu8(&c, 1)));
}
static b32
string_append_character(String_u16 *dst, u16 c){
    return(string_append(dst, SCu16(&c, 1)));
}
static b32
string_append_character(String_u32 *dst, u32 c){
    return(string_append(dst, SCu32(&c, 1)));
}

static b32
string_null_terminate(String_char *str){
    b32 result = false;
    if (str->size < str->cap){
        str->str[str->size] = 0;
    }
    return(result);
}
static b32
string_null_terminate(String_u8 *str){
    b32 result = false;
    if (str->size < str->cap){
        str->str[str->size] = 0;
    }
    return(result);
}
static b32
string_null_terminate(String_u16 *str){
    b32 result = false;
    if (str->size < str->cap){
        str->str[str->size] = 0;
    }
    return(result);
}
static b32
string_null_terminate(String_u32 *str){
    b32 result = false;
    if (str->size < str->cap){
        str->str[str->size] = 0;
    }
    return(result);
}

static String_char
string_char_push(Arena *arena, umem size){
    String_char string = {};
    string.str = push_array(arena, char, size);
    string.cap = size;
    return(string);
}
static String_u8
string_u8_push(Arena *arena, umem size){
    String_u8 string = {};
    string.str = push_array(arena, u8, size);
    string.cap = size;
    return(string);
}
static String_u16
string_u16_push(Arena *arena, umem size){
    String_u16 string = {};
    string.str = push_array(arena, u16, size);
    string.cap = size;
    return(string);
}
static String_u32
string_u32_push(Arena *arena, umem size){
    String_u32 string = {};
    string.str = push_array(arena, u32, size);
    string.cap = size;
    return(string);
}

static String_Any
string_any_push(Arena *arena, umem size, String_Encoding encoding){
    String_Any string = {};
    switch (encoding){
        case StringEncoding_ASCII: string.s_char = string_char_push(arena, size); break;
        case StringEncoding_UTF8:  string.s_u8   = string_u8_push  (arena, size); break;
        case StringEncoding_UTF16: string.s_u16  = string_u16_push (arena, size); break;
        case StringEncoding_UTF32: string.s_u32  = string_u32_push (arena, size); break;
    }
    return(string);
}

static String_Const_char
string_const_char_push(Arena *arena, umem size){
    String_Const_char string = {};
    string.str = push_array(arena, char, size);
    string.size = size;
    return(string);
}
static String_Const_u8
string_const_u8_push(Arena *arena, umem size){
    String_Const_u8 string = {};
    string.str = push_array(arena, u8, size);
    string.size = size;
    return(string);
}
static String_Const_u16
string_const_u16_push(Arena *arena, umem size){
    String_Const_u16 string = {};
    string.str = push_array(arena, u16, size);
    string.size = size;
    return(string);
}
static String_Const_u32
string_const_u32_push(Arena *arena, umem size){
    String_Const_u32 string = {};
    string.str = push_array(arena, u32, size);
    string.size = size;
    return(string);
}

static String_Const_Any
string_const_any_push(Arena *arena, umem size, String_Encoding encoding){
    String_Const_Any string = {};
    switch (encoding){
        case StringEncoding_ASCII: string.s_char = string_const_char_push(arena, size); break;
        case StringEncoding_UTF8:  string.s_u8   = string_const_u8_push  (arena, size); break;
        case StringEncoding_UTF16: string.s_u16  = string_const_u16_push (arena, size); break;
        case StringEncoding_UTF32: string.s_u32  = string_const_u32_push (arena, size); break;
    }
    return(string);
}

static String_Const_char
string_copy(Arena *arena, String_Const_char src){
    String_Const_char string = {};
    string.str = push_array(arena, char, src.size + 1);
    string.size = src.size;
    block_copy_dynamic_array(string.str, src.str, src.size);
    string.str[string.size] = 0;
    return(string);
}
static String_Const_u8
string_copy(Arena *arena, String_Const_u8 src){
    String_Const_u8 string = {};
    string.str = push_array(arena, u8, src.size + 1);
    string.size = src.size;
    block_copy_dynamic_array(string.str, src.str, src.size);
    string.str[string.size] = 0;
    return(string);
}
static String_Const_u16
string_copy(Arena *arena, String_Const_u16 src){
    String_Const_u16 string = {};
    string.str = push_array(arena, u16, src.size + 1);
    string.size = src.size;
    block_copy_dynamic_array(string.str, src.str, src.size);
    string.str[string.size] = 0;
    return(string);
}
static String_Const_u32
string_copy(Arena *arena, String_Const_u32 src){
    String_Const_u32 string = {};
    string.str = push_array(arena, u32, src.size + 1);
    string.size = src.size;
    block_copy_dynamic_array(string.str, src.str, src.size);
    string.str[string.size] = 0;
    return(string);
}

static String_Const_Any
string_copy(Arena *arena, umem size, String_Const_Any src){
    String_Const_Any string = {};
    switch (src.encoding){
        case StringEncoding_ASCII: string.s_char = string_copy(arena, src.s_char); break;
        case StringEncoding_UTF8:  string.s_u8   = string_copy(arena, src.s_u8  ); break;
        case StringEncoding_UTF16: string.s_u16  = string_copy(arena, src.s_u16 ); break;
        case StringEncoding_UTF32: string.s_u32  = string_copy(arena, src.s_u32 ); break;
    }
    return(string);
}

static void
string_list_push(Arena *arena, List_String_Const_char *list, String_Const_char string){
    Node_String_Const_char *node = push_array(arena, Node_String_Const_char, 1);
    sll_queue_push(list->first, list->last, node);
    node->string = string;
    list->node_count += 1;
    list->total_size += string.size;
}
static void
string_list_push(Arena *arena, List_String_Const_u8 *list, String_Const_u8 string){
    Node_String_Const_u8 *node = push_array(arena, Node_String_Const_u8, 1);
    sll_queue_push(list->first, list->last, node);
    node->string = string;
    list->node_count += 1;
    list->total_size += string.size;
}
static void
string_list_push(Arena *arena, List_String_Const_u16 *list, String_Const_u16 string){
    Node_String_Const_u16 *node = push_array(arena, Node_String_Const_u16, 1);
    sll_queue_push(list->first, list->last, node);
    node->string = string;
    list->node_count += 1;
    list->total_size += string.size;
}
static void
string_list_push(Arena *arena, List_String_Const_u32 *list, String_Const_u32 string){
    Node_String_Const_u32 *node = push_array(arena, Node_String_Const_u32, 1);
    sll_queue_push(list->first, list->last, node);
    node->string = string;
    list->node_count += 1;
    list->total_size += string.size;
}

static void
string_list_push(Arena *arena, List_String_Const_Any *list, String_Const_Any string){
    Node_String_Const_Any *node = push_array(arena, Node_String_Const_Any, 1);
    sll_queue_push(list->first, list->last, node);
    node->string = string;
    list->node_count += 1;
    list->total_size += string.size;
}

#define string_list_push_lit(a,l,s) string_list_push((a), (l), string_litexpr(s))
#define string_list_push_u8_lit(a,l,s) string_list_push((a), (l), string_u8_litexpr(s))

static void
string_list_push(List_String_Const_char *list, List_String_Const_char *src_list){
    sll_queue_push_multiple(list->first, list->last, src_list->first, src_list->last);
    list->node_count += src_list->node_count;
    list->total_size += src_list->total_size;
    block_zero_array(src_list);
}
static void
string_list_push(List_String_Const_u8 *list, List_String_Const_u8 *src_list){
    sll_queue_push_multiple(list->first, list->last, src_list->first, src_list->last);
    list->node_count += src_list->node_count;
    list->total_size += src_list->total_size;
    block_zero_array(src_list);
}
static void
string_list_push(List_String_Const_u16 *list, List_String_Const_u16 *src_list){
    sll_queue_push_multiple(list->first, list->last, src_list->first, src_list->last);
    list->node_count += src_list->node_count;
    list->total_size += src_list->total_size;
    block_zero_array(src_list);
}
static void
string_list_push(List_String_Const_u32 *list, List_String_Const_u32 *src_list){
    sll_queue_push_multiple(list->first, list->last, src_list->first, src_list->last);
    list->node_count += src_list->node_count;
    list->total_size += src_list->total_size;
    block_zero_array(src_list);
}

static void
string_list_push(List_String_Const_Any *list, List_String_Const_Any *src_list){
    sll_queue_push_multiple(list->first, list->last, src_list->first, src_list->last);
    list->node_count += src_list->node_count;
    list->total_size += src_list->total_size;
    block_zero_array(src_list);
}

static void
string_list_push_overlap(Arena *arena, List_String_Const_char *list, char overlap, String_Const_char string){
    b32 tail_has_overlap = false;
    b32 string_has_overlap = false;
    if (list->last != 0){
        String_Const_char tail = list->last->string;
        if (string_get_character(tail, tail.size - 1) == overlap){
            tail_has_overlap = true;
        }
    }
    if (string_get_character(string, 0) == overlap){
        string_has_overlap = true;
    }
    if (tail_has_overlap == string_has_overlap){
        if (!tail_has_overlap){
            string_list_push(arena, list, string_copy(arena, SCchar(&overlap, 1)));
        }
        else{
            string = string_skip(string, 1);
        }
    }
    if (string.size > 0){
        string_list_push(arena, list, string);
    }
}
static void
string_list_push_overlap(Arena *arena, List_String_Const_u8 *list, u8 overlap, String_Const_u8 string){
    b32 tail_has_overlap = false;
    b32 string_has_overlap = false;
    if (list->last != 0){
        String_Const_u8 tail = list->last->string;
        if (string_get_character(tail, tail.size - 1) == overlap){
            tail_has_overlap = true;
        }
    }
    if (string_get_character(string, 0) == overlap){
        string_has_overlap = true;
    }
    if (tail_has_overlap == string_has_overlap){
        if (!tail_has_overlap){
            string_list_push(arena, list, string_copy(arena, SCu8(&overlap, 1)));
        }
        else{
            string = string_skip(string, 1);
        }
    }
    if (string.size > 0){
        string_list_push(arena, list, string);
    }
}
static void
string_list_push_overlap(Arena *arena, List_String_Const_u16 *list, u16 overlap, String_Const_u16 string){
    b32 tail_has_overlap = false;
    b32 string_has_overlap = false;
    if (list->last != 0){
        String_Const_u16 tail = list->last->string;
        if (string_get_character(tail, tail.size - 1) == overlap){
            tail_has_overlap = true;
        }
    }
    if (string_get_character(string, 0) == overlap){
        string_has_overlap = true;
    }
    if (tail_has_overlap == string_has_overlap){
        if (!tail_has_overlap){
            string_list_push(arena, list, string_copy(arena, SCu16(&overlap, 1)));
        }
        else{
            string = string_skip(string, 1);
        }
    }
    if (string.size > 0){
        string_list_push(arena, list, string);
    }
}
static void
string_list_push_overlap(Arena *arena, List_String_Const_u32 *list, u32 overlap, String_Const_u32 string){
    b32 tail_has_overlap = false;
    b32 string_has_overlap = false;
    if (list->last != 0){
        String_Const_u32 tail = list->last->string;
        if (string_get_character(tail, tail.size - 1) == overlap){
            tail_has_overlap = true;
        }
    }
    if (string_get_character(string, 0) == overlap){
        string_has_overlap = true;
    }
    if (tail_has_overlap == string_has_overlap){
        if (!tail_has_overlap){
            string_list_push(arena, list, string_copy(arena, SCu32(&overlap, 1)));
        }
        else{
            string = string_skip(string, 1);
        }
    }
    if (string.size > 0){
        string_list_push(arena, list, string);
    }
}

typedef String_Const_char String_char_Mod_Function_Type(String_Const_char string);
typedef String_Const_u8 String_u8_Mod_Function_Type(String_Const_u8 string);
typedef String_Const_u16 String_u16_Mod_Function_Type(String_Const_u16 string);
typedef String_Const_u32 String_u32_Mod_Function_Type(String_Const_u32 string);

static String_Const_char
string_list_flatten(Arena *arena, List_String_Const_char list, String_char_Mod_Function_Type *mod, String_Const_char separator, String_Separator_Flag separator_flags, String_Fill_Terminate_Rule rule){
    umem term_padding = (rule == StringFill_NullTerminate)?(1):(0);b32 before_first = HasFlag(separator_flags, StringSeparator_BeforeFirst);
    b32 after_last = HasFlag(separator_flags, StringSeparator_AfterLast);
    umem separator_size = separator.size*(list.node_count + before_first + after_last - 1);
    String_char string = string_char_push(arena, list.total_size + separator_size + term_padding);
    if (before_first){
        string_append(&string, separator);
    }
    for (Node_String_Const_char *node = list.first;
         node != 0;
         node = node->next){
        block_copy_dynamic_array(string.str + string.size, node->string.str, node->string.size);
        if (mod != 0){
            mod(SCchar(string.str + string.size, node->string.size));
        }
        string.size += node->string.size;
        string_append(&string, separator);
    }
    if (after_last){
        string_append(&string, separator);
    }
    if (term_padding == 1){
        string_null_terminate(&string);
    }
    return(string.string);
}
static String_Const_u8
string_list_flatten(Arena *arena, List_String_Const_u8 list, String_u8_Mod_Function_Type *mod, String_Const_u8 separator, String_Separator_Flag separator_flags, String_Fill_Terminate_Rule rule){
    umem term_padding = (rule == StringFill_NullTerminate)?(1):(0);b32 before_first = HasFlag(separator_flags, StringSeparator_BeforeFirst);
    b32 after_last = HasFlag(separator_flags, StringSeparator_AfterLast);
    umem separator_size = separator.size*(list.node_count + before_first + after_last - 1);
    String_u8 string = string_u8_push(arena, list.total_size + separator_size + term_padding);
    if (before_first){
        string_append(&string, separator);
    }
    for (Node_String_Const_u8 *node = list.first;
         node != 0;
         node = node->next){
        block_copy_dynamic_array(string.str + string.size, node->string.str, node->string.size);
        if (mod != 0){
            mod(SCu8(string.str + string.size, node->string.size));
        }
        string.size += node->string.size;
        string_append(&string, separator);
    }
    if (after_last){
        string_append(&string, separator);
    }
    if (term_padding == 1){
        string_null_terminate(&string);
    }
    return(string.string);
}
static String_Const_u16
string_list_flatten(Arena *arena, List_String_Const_u16 list, String_u16_Mod_Function_Type *mod, String_Const_u16 separator, String_Separator_Flag separator_flags, String_Fill_Terminate_Rule rule){
    umem term_padding = (rule == StringFill_NullTerminate)?(1):(0);b32 before_first = HasFlag(separator_flags, StringSeparator_BeforeFirst);
    b32 after_last = HasFlag(separator_flags, StringSeparator_AfterLast);
    umem separator_size = separator.size*(list.node_count + before_first + after_last - 1);
    String_u16 string = string_u16_push(arena, list.total_size + separator_size + term_padding);
    if (before_first){
        string_append(&string, separator);
    }
    for (Node_String_Const_u16 *node = list.first;
         node != 0;
         node = node->next){
        block_copy_dynamic_array(string.str + string.size, node->string.str, node->string.size);
        if (mod != 0){
            mod(SCu16(string.str + string.size, node->string.size));
        }
        string.size += node->string.size;
        string_append(&string, separator);
    }
    if (after_last){
        string_append(&string, separator);
    }
    if (term_padding == 1){
        string_null_terminate(&string);
    }
    return(string.string);
}
static String_Const_u32
string_list_flatten(Arena *arena, List_String_Const_u32 list, String_u32_Mod_Function_Type *mod, String_Const_u32 separator, String_Separator_Flag separator_flags, String_Fill_Terminate_Rule rule){
    umem term_padding = (rule == StringFill_NullTerminate)?(1):(0);b32 before_first = HasFlag(separator_flags, StringSeparator_BeforeFirst);
    b32 after_last = HasFlag(separator_flags, StringSeparator_AfterLast);
    umem separator_size = separator.size*(list.node_count + before_first + after_last - 1);
    String_u32 string = string_u32_push(arena, list.total_size + separator_size + term_padding);
    if (before_first){
        string_append(&string, separator);
    }
    for (Node_String_Const_u32 *node = list.first;
         node != 0;
         node = node->next){
        block_copy_dynamic_array(string.str + string.size, node->string.str, node->string.size);
        if (mod != 0){
            mod(SCu32(string.str + string.size, node->string.size));
        }
        string.size += node->string.size;
        string_append(&string, separator);
    }
    if (after_last){
        string_append(&string, separator);
    }
    if (term_padding == 1){
        string_null_terminate(&string);
    }
    return(string.string);
}
static String_Const_char
string_list_flatten(Arena *arena, List_String_Const_char list, String_Const_char separator, String_Separator_Flag separator_flags, String_Fill_Terminate_Rule rule){
    return(string_list_flatten(arena, list, 0, separator, separator_flags, rule));
}
static String_Const_u8
string_list_flatten(Arena *arena, List_String_Const_u8 list, String_Const_u8 separator, String_Separator_Flag separator_flags, String_Fill_Terminate_Rule rule){
    return(string_list_flatten(arena, list, 0, separator, separator_flags, rule));
}
static String_Const_u16
string_list_flatten(Arena *arena, List_String_Const_u16 list, String_Const_u16 separator, String_Separator_Flag separator_flags, String_Fill_Terminate_Rule rule){
    return(string_list_flatten(arena, list, 0, separator, separator_flags, rule));
}
static String_Const_u32
string_list_flatten(Arena *arena, List_String_Const_u32 list, String_Const_u32 separator, String_Separator_Flag separator_flags, String_Fill_Terminate_Rule rule){
    return(string_list_flatten(arena, list, 0, separator, separator_flags, rule));
}
static String_Const_char
string_list_flatten(Arena *arena, List_String_Const_char list, String_char_Mod_Function_Type *mod, String_Fill_Terminate_Rule rule){
    return(string_list_flatten(arena, list, mod, SCchar(), 0, rule));
}
static String_Const_u8
string_list_flatten(Arena *arena, List_String_Const_u8 list, String_u8_Mod_Function_Type *mod, String_Fill_Terminate_Rule rule){
    return(string_list_flatten(arena, list, mod, SCu8(), 0, rule));
}
static String_Const_u16
string_list_flatten(Arena *arena, List_String_Const_u16 list, String_u16_Mod_Function_Type *mod, String_Fill_Terminate_Rule rule){
    return(string_list_flatten(arena, list, mod, SCu16(), 0, rule));
}
static String_Const_u32
string_list_flatten(Arena *arena, List_String_Const_u32 list, String_u32_Mod_Function_Type *mod, String_Fill_Terminate_Rule rule){
    return(string_list_flatten(arena, list, mod, SCu32(), 0, rule));
}
static String_Const_char
string_list_flatten(Arena *arena, List_String_Const_char string, String_Fill_Terminate_Rule rule){
    return(string_list_flatten(arena, string, 0, SCchar(), 0, rule));
}
static String_Const_u8
string_list_flatten(Arena *arena, List_String_Const_u8 string, String_Fill_Terminate_Rule rule){
    return(string_list_flatten(arena, string, 0, SCu8(), 0, rule));
}
static String_Const_u16
string_list_flatten(Arena *arena, List_String_Const_u16 string, String_Fill_Terminate_Rule rule){
    return(string_list_flatten(arena, string, 0, SCu16(), 0, rule));
}
static String_Const_u32
string_list_flatten(Arena *arena, List_String_Const_u32 string, String_Fill_Terminate_Rule rule){
    return(string_list_flatten(arena, string, 0, SCu32(), 0, rule));
}
static String_Const_char
string_list_flatten(Arena *arena, List_String_Const_char string){
    return(string_list_flatten(arena, string, 0, SCchar(), 0, StringFill_NoTerminate));
}
static String_Const_u8
string_list_flatten(Arena *arena, List_String_Const_u8 string){
    return(string_list_flatten(arena, string, 0, SCu8(), 0, StringFill_NoTerminate));
}
static String_Const_u16
string_list_flatten(Arena *arena, List_String_Const_u16 string){
    return(string_list_flatten(arena, string, 0, SCu16(), 0, StringFill_NoTerminate));
}
static String_Const_u32
string_list_flatten(Arena *arena, List_String_Const_u32 string){
    return(string_list_flatten(arena, string, 0, SCu32(), 0, StringFill_NoTerminate));
}

static List_String_Const_char
string_split(Arena *arena, String_Const_char string, char *split_characters, i32 split_character_count){
    List_String_Const_char list = {};
    for (;;){
        umem i = string.size;
        String_Const_char prefix = string;
        for (i32 j = 0; j < split_character_count; j += 1){
            umem pos = string_find_first(prefix, split_characters[j]);
            prefix = string_prefix(prefix, pos);
            i = min(i, pos);
        }
        if (prefix.size > 0){
            string_list_push(arena, &list, prefix);
        }
        string = string_skip(string, i + 1);
        if (string.size == 0){
            break;
        }
    }
    return(list);
}
static List_String_Const_u8
string_split(Arena *arena, String_Const_u8 string, u8 *split_characters, i32 split_character_count){
    List_String_Const_u8 list = {};
    for (;;){
        umem i = string.size;
        String_Const_u8 prefix = string;
        for (i32 j = 0; j < split_character_count; j += 1){
            umem pos = string_find_first(prefix, split_characters[j]);
            prefix = string_prefix(prefix, pos);
            i = min(i, pos);
        }
        if (prefix.size > 0){
            string_list_push(arena, &list, prefix);
        }
        string = string_skip(string, i + 1);
        if (string.size == 0){
            break;
        }
    }
    return(list);
}
static List_String_Const_u16
string_split(Arena *arena, String_Const_u16 string, u16 *split_characters, i32 split_character_count){
    List_String_Const_u16 list = {};
    for (;;){
        umem i = string.size;
        String_Const_u16 prefix = string;
        for (i32 j = 0; j < split_character_count; j += 1){
            umem pos = string_find_first(prefix, split_characters[j]);
            prefix = string_prefix(prefix, pos);
            i = min(i, pos);
        }
        if (prefix.size > 0){
            string_list_push(arena, &list, prefix);
        }
        string = string_skip(string, i + 1);
        if (string.size == 0){
            break;
        }
    }
    return(list);
}
static List_String_Const_u32
string_split(Arena *arena, String_Const_u32 string, u32 *split_characters, i32 split_character_count){
    List_String_Const_u32 list = {};
    for (;;){
        umem i = string.size;
        String_Const_u32 prefix = string;
        for (i32 j = 0; j < split_character_count; j += 1){
            umem pos = string_find_first(prefix, split_characters[j]);
            prefix = string_prefix(prefix, pos);
            i = min(i, pos);
        }
        if (prefix.size > 0){
            string_list_push(arena, &list, prefix);
        }
        string = string_skip(string, i + 1);
        if (string.size == 0){
            break;
        }
    }
    return(list);
}

static List_String_Const_char
string_split_needle(Arena *arena, String_Const_char string, String_Const_char needle){
    List_String_Const_char list = {};
    for (;string.size > 0;){
        umem pos = string_find_first(string, needle);
        String_Const_char prefix = string_prefix(string, pos);
        if (pos < string.size){
            string_list_push(arena, &list, needle);
        }
        if (prefix.size > 0){
            string_list_push(arena, &list, prefix);
        }
        string = string_skip(string, prefix.size + needle.size);
    }
    return(list);
}
static List_String_Const_u8
string_split_needle(Arena *arena, String_Const_u8 string, String_Const_u8 needle){
    List_String_Const_u8 list = {};
    for (;string.size > 0;){
        umem pos = string_find_first(string, needle);
        String_Const_u8 prefix = string_prefix(string, pos);
        if (pos < string.size){
            string_list_push(arena, &list, needle);
        }
        if (prefix.size > 0){
            string_list_push(arena, &list, prefix);
        }
        string = string_skip(string, prefix.size + needle.size);
    }
    return(list);
}
static List_String_Const_u16
string_split_needle(Arena *arena, String_Const_u16 string, String_Const_u16 needle){
    List_String_Const_u16 list = {};
    for (;string.size > 0;){
        umem pos = string_find_first(string, needle);
        String_Const_u16 prefix = string_prefix(string, pos);
        if (pos < string.size){
            string_list_push(arena, &list, needle);
        }
        if (prefix.size > 0){
            string_list_push(arena, &list, prefix);
        }
        string = string_skip(string, prefix.size + needle.size);
    }
    return(list);
}
static List_String_Const_u32
string_split_needle(Arena *arena, String_Const_u32 string, String_Const_u32 needle){
    List_String_Const_u32 list = {};
    for (;string.size > 0;){
        umem pos = string_find_first(string, needle);
        String_Const_u32 prefix = string_prefix(string, pos);
        if (pos < string.size){
            string_list_push(arena, &list, needle);
        }
        if (prefix.size > 0){
            string_list_push(arena, &list, prefix);
        }
        string = string_skip(string, prefix.size + needle.size);
    }
    return(list);
}

static void
string_list_insert_separators(Arena *arena, List_String_Const_char *list, String_Const_char separator, String_Separator_Flag flags){
    Node_String_Const_char *last = list->last;
    for (Node_String_Const_char *node = list->first, *next = 0;
         node != last;
         node = next){
        next = node->next;
        Node_String_Const_char *new_node = push_array(arena, Node_String_Const_char, 1);
        node->next = new_node;
        new_node->next = next;
        new_node->string = separator;
        list->node_count += 1;
        list->total_size += separator.size;
    }
    if (HasFlag(flags, StringSeparator_BeforeFirst)){
        Node_String_Const_char *new_node = push_array(arena, Node_String_Const_char, 1);
        new_node->next = list->first;
        list->first = new_node;
        new_node->string = separator;
        list->node_count += 1;
        list->total_size += separator.size;
    }
    if (HasFlag(flags, StringSeparator_AfterLast)){
        Node_String_Const_char *new_node = push_array(arena, Node_String_Const_char, 1);
        list->last->next = new_node;
        list->last = new_node;
        new_node->next = 0;
        new_node->string = separator;
        list->node_count += 1;
        list->total_size += separator.size;
    }
}
static void
string_list_insert_separators(Arena *arena, List_String_Const_u8 *list, String_Const_u8 separator, String_Separator_Flag flags){
    Node_String_Const_u8 *last = list->last;
    for (Node_String_Const_u8 *node = list->first, *next = 0;
         node != last;
         node = next){
        next = node->next;
        Node_String_Const_u8 *new_node = push_array(arena, Node_String_Const_u8, 1);
        node->next = new_node;
        new_node->next = next;
        new_node->string = separator;
        list->node_count += 1;
        list->total_size += separator.size;
    }
    if (HasFlag(flags, StringSeparator_BeforeFirst)){
        Node_String_Const_u8 *new_node = push_array(arena, Node_String_Const_u8, 1);
        new_node->next = list->first;
        list->first = new_node;
        new_node->string = separator;
        list->node_count += 1;
        list->total_size += separator.size;
    }
    if (HasFlag(flags, StringSeparator_AfterLast)){
        Node_String_Const_u8 *new_node = push_array(arena, Node_String_Const_u8, 1);
        list->last->next = new_node;
        list->last = new_node;
        new_node->next = 0;
        new_node->string = separator;
        list->node_count += 1;
        list->total_size += separator.size;
    }
}
static void
string_list_insert_separators(Arena *arena, List_String_Const_u16 *list, String_Const_u16 separator, String_Separator_Flag flags){
    Node_String_Const_u16 *last = list->last;
    for (Node_String_Const_u16 *node = list->first, *next = 0;
         node != last;
         node = next){
        next = node->next;
        Node_String_Const_u16 *new_node = push_array(arena, Node_String_Const_u16, 1);
        node->next = new_node;
        new_node->next = next;
        new_node->string = separator;
        list->node_count += 1;
        list->total_size += separator.size;
    }
    if (HasFlag(flags, StringSeparator_BeforeFirst)){
        Node_String_Const_u16 *new_node = push_array(arena, Node_String_Const_u16, 1);
        new_node->next = list->first;
        list->first = new_node;
        new_node->string = separator;
        list->node_count += 1;
        list->total_size += separator.size;
    }
    if (HasFlag(flags, StringSeparator_AfterLast)){
        Node_String_Const_u16 *new_node = push_array(arena, Node_String_Const_u16, 1);
        list->last->next = new_node;
        list->last = new_node;
        new_node->next = 0;
        new_node->string = separator;
        list->node_count += 1;
        list->total_size += separator.size;
    }
}
static void
string_list_insert_separators(Arena *arena, List_String_Const_u32 *list, String_Const_u32 separator, String_Separator_Flag flags){
    Node_String_Const_u32 *last = list->last;
    for (Node_String_Const_u32 *node = list->first, *next = 0;
         node != last;
         node = next){
        next = node->next;
        Node_String_Const_u32 *new_node = push_array(arena, Node_String_Const_u32, 1);
        node->next = new_node;
        new_node->next = next;
        new_node->string = separator;
        list->node_count += 1;
        list->total_size += separator.size;
    }
    if (HasFlag(flags, StringSeparator_BeforeFirst)){
        Node_String_Const_u32 *new_node = push_array(arena, Node_String_Const_u32, 1);
        new_node->next = list->first;
        list->first = new_node;
        new_node->string = separator;
        list->node_count += 1;
        list->total_size += separator.size;
    }
    if (HasFlag(flags, StringSeparator_AfterLast)){
        Node_String_Const_u32 *new_node = push_array(arena, Node_String_Const_u32, 1);
        list->last->next = new_node;
        list->last = new_node;
        new_node->next = 0;
        new_node->string = separator;
        list->node_count += 1;
        list->total_size += separator.size;
    }
}

static void
string_list_rewrite_nodes(Arena *arena, List_String_Const_char *list, String_Const_char needle, String_Const_char new_value){
    for (Node_String_Const_char *node = list->first;
         node != 0;
         node = node->next){
        if (string_match(node->string, needle)){
            node->string = new_value;
            list->total_size += new_value.size;
            list->total_size -= needle.size;
        }
    }
}
static void
string_list_rewrite_nodes(Arena *arena, List_String_Const_u8 *list, String_Const_u8 needle, String_Const_u8 new_value){
    for (Node_String_Const_u8 *node = list->first;
         node != 0;
         node = node->next){
        if (string_match(node->string, needle)){
            node->string = new_value;
            list->total_size += new_value.size;
            list->total_size -= needle.size;
        }
    }
}
static void
string_list_rewrite_nodes(Arena *arena, List_String_Const_u16 *list, String_Const_u16 needle, String_Const_u16 new_value){
    for (Node_String_Const_u16 *node = list->first;
         node != 0;
         node = node->next){
        if (string_match(node->string, needle)){
            node->string = new_value;
            list->total_size += new_value.size;
            list->total_size -= needle.size;
        }
    }
}
static void
string_list_rewrite_nodes(Arena *arena, List_String_Const_u32 *list, String_Const_u32 needle, String_Const_u32 new_value){
    for (Node_String_Const_u32 *node = list->first;
         node != 0;
         node = node->next){
        if (string_match(node->string, needle)){
            node->string = new_value;
            list->total_size += new_value.size;
            list->total_size -= needle.size;
        }
    }
}

static String_Const_char
string_condense_whitespace(Arena *arena, String_Const_char string){
    char split_characters[] = { ' ', '\t', '\n', '\r', '\f', '\v', };
    List_String_Const_char list = string_split(arena, string, split_characters, ArrayCount(split_characters));
    string_list_insert_separators(arena, &list, SCchar(split_characters, 1), StringSeparator_NoFlags);
    return(string_list_flatten(arena, list, StringFill_NullTerminate));
}
static String_Const_u8
string_condense_whitespace(Arena *arena, String_Const_u8 string){
    u8 split_characters[] = { ' ', '\t', '\n', '\r', '\f', '\v', };
    List_String_Const_u8 list = string_split(arena, string, split_characters, ArrayCount(split_characters));
    string_list_insert_separators(arena, &list, SCu8(split_characters, 1), StringSeparator_NoFlags);
    return(string_list_flatten(arena, list, StringFill_NullTerminate));
}
static String_Const_u16
string_condense_whitespace(Arena *arena, String_Const_u16 string){
    u16 split_characters[] = { ' ', '\t', '\n', '\r', '\f', '\v', };
    List_String_Const_u16 list = string_split(arena, string, split_characters, ArrayCount(split_characters));
    string_list_insert_separators(arena, &list, SCu16(split_characters, 1), StringSeparator_NoFlags);
    return(string_list_flatten(arena, list, StringFill_NullTerminate));
}
static String_Const_u32
string_condense_whitespace(Arena *arena, String_Const_u32 string){
    u32 split_characters[] = { ' ', '\t', '\n', '\r', '\f', '\v', };
    List_String_Const_u32 list = string_split(arena, string, split_characters, ArrayCount(split_characters));
    string_list_insert_separators(arena, &list, SCu32(split_characters, 1), StringSeparator_NoFlags);
    return(string_list_flatten(arena, list, StringFill_NullTerminate));
}

static List_String_Const_u8
string_split_wildcards(Arena *arena, String_Const_u8 string){
    List_String_Const_u8 list = {};
    if (string_get_character(string, 0) == '*'){
        string_list_push(arena, &list, SCu8());
    }
    {
        List_String_Const_u8 splits = string_split(arena, string, (u8*)"*", 1);
        string_list_push(&list, &splits);
    }
    if (string.size > 1 && string_get_character(string, string.size - 1) == '*'){
        string_list_push(arena, &list, SCu8());
    }
    return(list);
}

static b32
string_wildcard_match(List_String_Const_u8 list, String_Const_u8 string, String_Match_Rule rule){
    b32 success = true;
    if (list.node_count > 0){
        String_Const_u8 head = list.first->string;
        if (!string_match(head, string_prefix(string, head.size), rule)){
            success = false;
        }
        else if (list.node_count > 1){
            string = string_skip(string, head.size);
            String_Const_u8 tail = list.last->string;
            if (!string_match(tail, string_postfix(string, tail.size), rule)){
                success = false;
            }
            else if (list.node_count > 2){
                string = string_chop(string, tail.size);
                Node_String_Const_u8 *one_past_last = list.last;
                for (Node_String_Const_u8 *node = list.first->next;
                     node != one_past_last;
                     node = node->next){
                    umem position = string_find_first(string, node->string, rule);
                    if (position < string.size){
                        string = string_skip(string, position + node->string.size);
                    }
                    else{
                        success = false;
                        break;
                    }
                }
            }
        }
    }
    return(success);
}

static b32
string_wildcard_match(List_String_Const_u8 list, String_Const_u8 string){
    return(string_wildcard_match(list, string, StringMatch_Exact));
}
static b32
string_wildcard_match_insensitive(List_String_Const_u8 list, String_Const_u8 string){
    return(string_wildcard_match(list, string, StringMatch_CaseInsensitive));
}

////////////////////////////////

global_const u8 utf8_class[32] = {
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,2,2,2,2,3,3,4,5,
};

static Character_Consume_Result
utf8_consume(u8 *str, umem max){
    Character_Consume_Result result = {1, max_u32};
    u8 byte = str[0];
    u8 byte_class = utf8_class[byte >> 3];
    switch (byte_class){
        case 1:
        {
            result.codepoint = byte;
        }break;
        case 2:
        {
            if (1 < max){
                u8 cont_byte = str[1];
                if (utf8_class[cont_byte >> 3] == 0){
                    result.codepoint = (byte & bitmask_5) << 6;
                    result.codepoint |= (cont_byte & bitmask_6);
                    result.inc = 2;
                }
            }
        }break;
        case 3:
        {
            if (2 < max){
                u8 cont_byte[2] = {str[1], str[2]};
                if (utf8_class[cont_byte[0] >> 3] == 0 &&
                    utf8_class[cont_byte[1] >> 3] == 0){
                    result.codepoint = (byte & bitmask_4) << 12;
                    result.codepoint |= ((cont_byte[0] & bitmask_6) << 6);
                    result.codepoint |=  (cont_byte[1] & bitmask_6);
                    result.inc = 3;
                }
            }
        }break;
        case 4:
        {
            if (3 < max){
                u8 cont_byte[3] = {str[1], str[2], str[3]};
                if (utf8_class[cont_byte[0] >> 3] == 0 &&
                    utf8_class[cont_byte[1] >> 3] == 0 &&
                    utf8_class[cont_byte[2] >> 3] == 0){
                    result.codepoint = (byte & bitmask_3) << 18;
                    result.codepoint |= ((cont_byte[0] & bitmask_6) << 12);
                    result.codepoint |= ((cont_byte[1] & bitmask_6) <<  6);
                    result.codepoint |=  (cont_byte[2] & bitmask_6);
                    result.inc = 4;
                }
            }
        }break;
    }
    return(result);
}

static Character_Consume_Result
utf16_consume(u16 *str, umem max){
    Character_Consume_Result result = {1, max_u32};
    result.codepoint = str[0];
    result.inc = 1;
    if (0xD800 <= str[0] && str[0] < 0xDC00 && max > 1 && 0xDC00 <= str[1] && str[1] < 0xE000){
        result.codepoint = ((str[0] - 0xD800) << 10) | (str[1] - 0xDC00);
        result.inc = 2;
    }
    return(result);
}

static u32
utf8_write(u8 *str, u32 codepoint){
    u32 inc = 0;
    if (codepoint <= 0x7F){
        str[0] = (u8)codepoint;
        inc = 1;
    }
    else if (codepoint <= 0x7FF){
        str[0] = (bitmask_2 << 6) | ((codepoint >> 6) & bitmask_5);
        str[1] = bit_8 | (codepoint & bitmask_6);
        inc = 2;
    }
    else if (codepoint <= 0xFFFF){
        str[0] = (bitmask_3 << 5) | ((codepoint >> 12) & bitmask_4);
        str[1] = bit_8 | ((codepoint >> 6) & bitmask_6);
        str[2] = bit_8 | ( codepoint       & bitmask_6);
        inc = 3;
    }
    else if (codepoint <= 0x10FFFF){
        str[0] = (bitmask_4 << 3) | ((codepoint >> 18) & bitmask_3);
        str[1] = bit_8 | ((codepoint >> 12) & bitmask_6);
        str[2] = bit_8 | ((codepoint >>  6) & bitmask_6);
        str[3] = bit_8 | ( codepoint        & bitmask_6);
        inc = 4;
    }
    else{
        str[0] = '?';
        inc = 1;
    }
    return(inc);
}

static u32
utf16_write(u16 *str, u32 codepoint){
    u32 inc = 1;
    if (codepoint == max_u32){
        str[0] = (u16)'?';
    }
    else if (codepoint < 0x10000){
        str[0] = (u16)codepoint;
    }
    else{
        u32 v = codepoint - 0x10000;
        str[0] = 0xD800 + (u16)(v >> 10);
        str[1] = 0xDC00 + (v & bitmask_10);
        inc = 2;
    }
    return(inc);
}

////////////////////////////////

static String_u8
string_u8_from_string_char(Arena *arena, String_Const_char string, String_Fill_Terminate_Rule rule){
    String_u8 out = {};
    out.cap = string.size;
    if (rule == StringFill_NullTerminate){
        out.cap += 1;
    }
    out.str = push_array(arena, u8, out.cap);
    for (umem i = 0; i < string.size; i += 1){
        out.str[i] = ((u8)string.str[i])&bitmask_7;
    }
    out.size = string.size;
    if (rule == StringFill_NullTerminate){
        string_null_terminate(&out);
    }
    return(out);
}

static String_u16
string_u16_from_string_char(Arena *arena, String_Const_char string, String_Fill_Terminate_Rule rule){
    String_u16 out = {};
    out.cap = string.size;
    if (rule == StringFill_NullTerminate){
        out.cap += 1;
    }
    out.str = push_array(arena, u16, out.cap);
    for (umem i = 0; i < string.size; i += 1){
        out.str[i] = ((u16)string.str[i])&bitmask_7;
    }
    out.size = string.size;
    if (rule == StringFill_NullTerminate){
        string_null_terminate(&out);
    }
    return(out);
}

static String_u32
string_u32_from_string_char(Arena *arena, String_Const_char string, String_Fill_Terminate_Rule rule){
    String_u32 out = {};
    out.cap = string.size;
    if (rule == StringFill_NullTerminate){
        out.cap += 1;
    }
    out.str = push_array(arena, u32, string.size);
    for (umem i = 0; i < string.size; i += 1){
        out.str[i] = ((u32)string.str[i])&bitmask_7;
    }
    out.size = string.size;
    if (rule == StringFill_NullTerminate){
        string_null_terminate(&out);
    }
    return(out);
}

static String_char
string_char_from_string_u8(Arena *arena, String_Const_u8 string, String_Fill_Terminate_Rule rule){
    String_char out = {};
    out.cap = string.size;
    if (rule == StringFill_NullTerminate){
        out.cap += 1;
    }
    out.str = push_array(arena, char, out.cap);
    u8 *ptr = string.str;
    u8 *one_past_last = ptr + string.size;
    umem cap = string.size;
    Character_Consume_Result consume;
    for (;ptr < one_past_last; ptr += consume.inc, cap -= consume.inc){
        consume = utf8_consume(ptr, cap);
        out.str[out.size++] = (consume.codepoint <= 127)?((char)consume.codepoint):('?');
    }
    if (rule == StringFill_NullTerminate){
        string_null_terminate(&out);
    }
    return(out);
}

static String_u16
string_u16_from_string_u8(Arena *arena, String_Const_u8 string, String_Fill_Terminate_Rule rule){
    String_u16 out = {};
    out.cap = string.size;
    if (rule == StringFill_NullTerminate){
        out.cap += 1;
    }
    out.str = push_array(arena, u16, out.cap);
    u8 *ptr = string.str;
    u8 *one_past_last = ptr + string.size;
    umem cap = string.size;
    Character_Consume_Result consume;
    for (;ptr < one_past_last; ptr += consume.inc, cap -= consume.inc){
        consume = utf8_consume(ptr, cap);
        out.size += utf16_write(out.str + out.size, consume.codepoint);
    }
    if (rule == StringFill_NullTerminate){
        string_null_terminate(&out);
    }
    return(out);
}

static String_u32
string_u32_from_string_u8(Arena *arena, String_Const_u8 string, String_Fill_Terminate_Rule rule){
    String_u32 out = {};
    out.cap = string.size;
    if (rule == StringFill_NullTerminate){
        out.cap += 1;
    }
    out.str = push_array(arena, u32, out.cap);
    u8 *ptr = string.str;
    u8 *one_past_last = ptr + string.size;
    umem cap = string.size;
    Character_Consume_Result consume;
    for (;ptr < one_past_last; ptr += consume.inc, cap -= consume.inc){
        consume = utf8_consume(ptr, cap);
        out.str[out.size++] = (consume.codepoint == max_u32)?(u64)'?':(consume.codepoint);
    }
    if (rule == StringFill_NullTerminate){
        string_null_terminate(&out);
    }
    return(out);
}

static String_char
string_char_from_string_u16(Arena *arena, String_Const_u16 string, String_Fill_Terminate_Rule rule){
    String_char out = {};
    out.cap = string.size;
    if (rule == StringFill_NullTerminate){
        out.cap += 1;
    }
    out.str = push_array(arena, char, out.cap);
    u16 *ptr = string.str;
    u16 *one_past_last = ptr + string.size;
    umem cap = string.size;
    Character_Consume_Result consume;
    for (;ptr < one_past_last; ptr += consume.inc, cap -= consume.inc){
        consume = utf16_consume(ptr, cap);
        out.str[out.size++] = (consume.codepoint <= 127)?((char)consume.codepoint):('?');
    }
    if (rule == StringFill_NullTerminate){
        string_null_terminate(&out);
    }
    return(out);
}

static String_u8
string_u8_from_string_u16(Arena *arena, String_Const_u16 string, String_Fill_Terminate_Rule rule){
    String_u8 out = {};
    out.cap = string.size*3;
    if (rule == StringFill_NullTerminate){
        out.cap += 1;
    }
    out.str = push_array(arena, u8, out.cap);
    u16 *ptr = string.str;
    u16 *one_past_last = ptr + string.size;
    umem cap = string.size;
    Character_Consume_Result consume;
    for (;ptr < one_past_last; ptr += consume.inc, cap -= consume.inc){
        consume = utf16_consume(ptr, cap);
        out.size += utf8_write(out.str + out.size, consume.codepoint);
    }
    if (rule == StringFill_NullTerminate){
        string_null_terminate(&out);
    }
    return(out);
}

static String_u32
string_u32_from_string_u16(Arena *arena, String_Const_u16 string, String_Fill_Terminate_Rule rule){
    String_u32 out = {};
    out.cap = string.size;
    if (rule == StringFill_NullTerminate){
        out.cap += 1;
    }
    out.str = push_array(arena, u32, out.cap);
    u16 *ptr = string.str;
    u16 *one_past_last = ptr + string.size;
    umem cap = string.size;
    Character_Consume_Result consume;
    for (;ptr < one_past_last; ptr += consume.inc, cap -= consume.inc){
        consume = utf16_consume(ptr, cap);
        out.str[out.size++] = consume.codepoint;
    }
    if (rule == StringFill_NullTerminate){
        string_null_terminate(&out);
    }
    return(out);
}

static String_char
string_char_from_string_u32(Arena *arena, String_Const_u32 string, String_Fill_Terminate_Rule rule){
    String_char out = {};
    out.cap = string.size;
    if (rule == StringFill_NullTerminate){
        out.cap += 1;
    }
    out.str = push_array(arena, char, string.size);
    u32 *ptr = string.str;
    u32 *one_past_last = ptr + string.size;
    for (;ptr < one_past_last; ptr += 1){
        u32 codepoint = *ptr;
        out.str[out.size++] = (codepoint <= 127)?((char)codepoint):('?');
    }
    if (rule == StringFill_NullTerminate){
        string_null_terminate(&out);
    }
    return(out);
}

static String_u8
string_u8_from_string_u32(Arena *arena, String_Const_u32 string, String_Fill_Terminate_Rule rule){
    String_u8 out = {};
    out.cap = string.size*4;
    if (rule == StringFill_NullTerminate){
        out.cap += 1;
    }
    out.str = push_array(arena, u8, out.cap);
    u32 *ptr = string.str;
    u32 *one_past_last = ptr + string.size;
    for (;ptr < one_past_last; ptr += 1){
        out.size += utf8_write(out.str + out.size, *ptr);
    }
    if (rule == StringFill_NullTerminate){
        string_null_terminate(&out);
    }
    return(out);
}

static String_u16
string_u16_from_string_u32(Arena *arena, String_Const_u32 string, String_Fill_Terminate_Rule rule){
    String_u16 out = {};
    out.cap = string.size*2;
    if (rule == StringFill_NullTerminate){
        out.cap += 1;
    }
    out.str = push_array(arena, u16, out.cap);
    u32 *ptr = string.str;
    u32 *one_past_last = ptr + string.size;
    for (;ptr < one_past_last; ptr += 1){
        out.size += utf16_write(out.str + out.size, *ptr);
    }
    if (rule == StringFill_NullTerminate){
        string_null_terminate(&out);
    }
    return(out);
}

////////////////////////////////

static String_char
string_char_from_string_u8(Arena *arena, String_Const_u8 string){
    return(string_char_from_string_u8(arena, string, StringFill_NoTerminate));
}
static String_char
string_char_from_string_u16(Arena *arena, String_Const_u16 string){
    return(string_char_from_string_u16(arena, string, StringFill_NoTerminate));
}
static String_char
string_char_from_string_u32(Arena *arena, String_Const_u32 string){
    return(string_char_from_string_u32(arena, string, StringFill_NoTerminate));
}
static String_u8
string_u8_from_string_char(Arena *arena, String_Const_char string){
    return(string_u8_from_string_char(arena, string, StringFill_NoTerminate));
}
static String_u8
string_u8_from_string_u16(Arena *arena, String_Const_u16 string){
    return(string_u8_from_string_u16(arena, string, StringFill_NoTerminate));
}
static String_u8
string_u8_from_string_u32(Arena *arena, String_Const_u32 string){
    return(string_u8_from_string_u32(arena, string, StringFill_NoTerminate));
}
static String_u16
string_u16_from_string_char(Arena *arena, String_Const_char string){
    return(string_u16_from_string_char(arena, string, StringFill_NoTerminate));
}
static String_u16
string_u16_from_string_u8(Arena *arena, String_Const_u8 string){
    return(string_u16_from_string_u8(arena, string, StringFill_NoTerminate));
}
static String_u16
string_u16_from_string_u32(Arena *arena, String_Const_u32 string){
    return(string_u16_from_string_u32(arena, string, StringFill_NoTerminate));
}
static String_u32
string_u32_from_string_char(Arena *arena, String_Const_char string){
    return(string_u32_from_string_char(arena, string, StringFill_NoTerminate));
}
static String_u32
string_u32_from_string_u8(Arena *arena, String_Const_u8 string){
    return(string_u32_from_string_u8(arena, string, StringFill_NoTerminate));
}
static String_u32
string_u32_from_string_u16(Arena *arena, String_Const_u16 string){
    return(string_u32_from_string_u16(arena, string, StringFill_NoTerminate));
}

////////////////////////////////

static String_Const_char
string_char_from_any(Arena *arena, String_Const_Any string){
    String_Const_char result = {};
    switch (string.encoding){
        case StringEncoding_ASCII: result = string.s_char; break;
        case StringEncoding_UTF8:  result = string_char_from_string_u8 (arena, string.s_u8 ).string; break;
        case StringEncoding_UTF16: result = string_char_from_string_u16(arena, string.s_u16).string; break;
        case StringEncoding_UTF32: result = string_char_from_string_u32(arena, string.s_u32).string; break;
    }
    return(result);
}
static String_Const_u8
string_u8_from_any(Arena *arena, String_Const_Any string){
    String_Const_u8 result = {};
    switch (string.encoding){
        case StringEncoding_ASCII: result = string_u8_from_string_char(arena, string.s_char).string; break;
        case StringEncoding_UTF8:  result = string.s_u8; break;
        case StringEncoding_UTF16: result = string_u8_from_string_u16(arena, string.s_u16).string; break;
        case StringEncoding_UTF32: result = string_u8_from_string_u32(arena, string.s_u32).string; break;
    }
    return(result);
}
static String_Const_u16
string_u16_from_any(Arena *arena, String_Const_Any string){
    String_Const_u16 result = {};
    switch (string.encoding){
        case StringEncoding_ASCII: result = string_u16_from_string_char(arena, string.s_char).string; break;
        case StringEncoding_UTF8:  result = string_u16_from_string_u8  (arena, string.s_u8  ).string; break;
        case StringEncoding_UTF16: result = string.s_u16; break;
        case StringEncoding_UTF32: result = string_u16_from_string_u32(arena, string.s_u32).string; break;
    }
    return(result);
}
static String_Const_u32
string_u32_from_any(Arena *arena, String_Const_Any string){
    String_Const_u32 result = {};
    switch (string.encoding){
        case StringEncoding_ASCII: result = string_u32_from_string_char(arena, string.s_char).string; break;
        case StringEncoding_UTF8:  result = string_u32_from_string_u8  (arena, string.s_u8  ).string; break;
        case StringEncoding_UTF16: result = string_u32_from_string_u16 (arena, string.s_u16 ).string; break;
        case StringEncoding_UTF32: result = string.s_u32; break;
    }
    return(result);
}

static String_Const_Any
string_any_from_any(Arena *arena, String_Encoding encoding, String_Const_Any string){
    String_Const_Any result = {encoding};
    switch (encoding){
        case StringEncoding_ASCII: result.s_char = string_char_from_any(arena, string); break;
        case StringEncoding_UTF8:  result.s_u8   = string_u8_from_any  (arena, string); break;
        case StringEncoding_UTF16: result.s_u16  = string_u16_from_any (arena, string); break;
        case StringEncoding_UTF32: result.s_u32  = string_u32_from_any (arena, string); break;
    }
    return(result);
}

static List_String_Const_char
string_list_char_from_any(Arena *arena, List_String_Const_Any list){
    List_String_Const_char result = {};
    for (Node_String_Const_Any *node = list.first;
         node != 0;
         node = node->next){
        string_list_push(arena, &result, string_char_from_any(arena, node->string));
    }
    return(result);
}
static List_String_Const_u8
string_list_u8_from_any(Arena *arena, List_String_Const_Any list){
    List_String_Const_u8 result = {};
    for (Node_String_Const_Any *node = list.first;
         node != 0;
         node = node->next){
        string_list_push(arena, &result, string_u8_from_any(arena, node->string));
    }
    return(result);
}
static List_String_Const_u16
string_list_u16_from_any(Arena *arena, List_String_Const_Any list){
    List_String_Const_u16 result = {};
    for (Node_String_Const_Any *node = list.first;
         node != 0;
         node = node->next){
        string_list_push(arena, &result, string_u16_from_any(arena, node->string));
    }
    return(result);
}
static List_String_Const_u32
string_list_u32_from_any(Arena *arena, List_String_Const_Any list){
    List_String_Const_u32 result = {};
    for (Node_String_Const_Any *node = list.first;
         node != 0;
         node = node->next){
        string_list_push(arena, &result, string_u32_from_any(arena, node->string));
    }
    return(result);
}

////////////////////////////////

static List_String_Const_char
string_replace_list(Arena *arena, String_Const_char source, String_Const_char needle, String_Const_char replacement){
    List_String_Const_char list = {};
    for (;;){
        umem i = string_find_first(source, needle);
        string_list_push(arena, &list, string_prefix(source, i));
        if (i < source.size){
            string_list_push(arena, &list, replacement);
            source = string_skip(source, i + needle.size);
        }
        else{
            break;
        }
    }
    return(list);
}
static List_String_Const_u8
string_replace_list(Arena *arena, String_Const_u8 source, String_Const_u8 needle, String_Const_u8 replacement){
    List_String_Const_u8 list = {};
    for (;;){
        umem i = string_find_first(source, needle);
        string_list_push(arena, &list, string_prefix(source, i));
        if (i < source.size){
            string_list_push(arena, &list, replacement);
            source = string_skip(source, i + needle.size);
        }
        else{
            break;
        }
    }
    return(list);
}
static List_String_Const_u16
string_replace_list(Arena *arena, String_Const_u16 source, String_Const_u16 needle, String_Const_u16 replacement){
    List_String_Const_u16 list = {};
    for (;;){
        umem i = string_find_first(source, needle);
        string_list_push(arena, &list, string_prefix(source, i));
        if (i < source.size){
            string_list_push(arena, &list, replacement);
            source = string_skip(source, i + needle.size);
        }
        else{
            break;
        }
    }
    return(list);
}
static List_String_Const_u32
string_replace_list(Arena *arena, String_Const_u32 source, String_Const_u32 needle, String_Const_u32 replacement){
    List_String_Const_u32 list = {};
    for (;;){
        umem i = string_find_first(source, needle);
        string_list_push(arena, &list, string_prefix(source, i));
        if (i < source.size){
            string_list_push(arena, &list, replacement);
            source = string_skip(source, i + needle.size);
        }
        else{
            break;
        }
    }
    return(list);
}

static String_Const_char
string_replace(Arena *arena, String_Const_char source, String_Const_char needle, String_Const_char replacement, String_Fill_Terminate_Rule rule){
    List_String_Const_char list = string_replace_list(arena, source, needle, replacement);
    return(string_list_flatten(arena, list, rule));
}
static String_Const_u8
string_replace(Arena *arena, String_Const_u8 source, String_Const_u8 needle, String_Const_u8 replacement, String_Fill_Terminate_Rule rule){
    List_String_Const_u8 list = string_replace_list(arena, source, needle, replacement);
    return(string_list_flatten(arena, list, rule));
}
static String_Const_u16
string_replace(Arena *arena, String_Const_u16 source, String_Const_u16 needle, String_Const_u16 replacement, String_Fill_Terminate_Rule rule){
    List_String_Const_u16 list = string_replace_list(arena, source, needle, replacement);
    return(string_list_flatten(arena, list, rule));
}
static String_Const_u32
string_replace(Arena *arena, String_Const_u32 source, String_Const_u32 needle, String_Const_u32 replacement, String_Fill_Terminate_Rule rule){
    List_String_Const_u32 list = string_replace_list(arena, source, needle, replacement);
    return(string_list_flatten(arena, list, rule));
}

static String_Const_char
string_replace(Arena *arena, String_Const_char source, String_Const_char needle, String_Const_char replacement){
    return(string_replace(arena, source, needle, replacement, StringFill_NoTerminate));
}
static String_Const_u8
string_replace(Arena *arena, String_Const_u8 source, String_Const_u8 needle, String_Const_u8 replacement){
    return(string_replace(arena, source, needle, replacement, StringFill_NoTerminate));
}
static String_Const_u16
string_replace(Arena *arena, String_Const_u16 source, String_Const_u16 needle, String_Const_u16 replacement){
    return(string_replace(arena, source, needle, replacement, StringFill_NoTerminate));
}
static String_Const_u32
string_replace(Arena *arena, String_Const_u32 source, String_Const_u32 needle, String_Const_u32 replacement){
    return(string_replace(arena, source, needle, replacement, StringFill_NoTerminate));
}

////////////////////////////////

static b32
byte_is_ascii(u8 byte){
    return(byte == '\r' || byte == '\n' || byte == '\t' || (' ' <= byte && byte <= '~'));
}

static b32
data_is_ascii(Data data){
    u8 *ptr = (u8*)data.data;
    u8 *one_past_last = ptr + data.size;
    b32 result = true;
    for (;ptr < one_past_last; ptr += 1){
        if (!byte_is_ascii(*ptr) && !(*ptr == 0 && ptr + 1 == one_past_last)){
            result = false;
            break;
        }
    }
    return(result);
}

////////////////////////////////

static String_Const_char
string_interpret_escapes(Arena *arena, String_Const_char string){
    char *space = push_array(arena, char, string.size + 1);
    String_char result = Schar(space, 0, string.size);
    for (;;){
        umem back_slash_pos = string_find_first(string, '\\');
        string_append(&result, string_prefix(string, back_slash_pos));
        string = string_skip(string, back_slash_pos + 1);
        if (string.size == 0){
            break;
        }
        switch (string.str[0]){
            case '\\':
            {
                string_append_character(&result, '\\');
            }break;
            
            case 'n':
            {
                string_append_character(&result, '\n');
            }break;
            
            case 't':
            {
                string_append_character(&result, '\t');
            }break;
            
            case '"':
            {
                string_append_character(&result, '\"');
            }break;
            
            case '0':
            {
                string_append_character(&result, '\0');
            }break;
            
            default:
            {
                char c[2] = {'\\'};
                c[1] = string.str[0];
                string_append(&result, SCchar(c, 2));
            }break;
        }
        string = string_skip(string, 1);
    }
    result.str[result.size] = 0;
    pop_array(arena, char, result.cap - result.size);
    return(result.string);
}

static String_Const_u8
string_interpret_escapes(Arena *arena, String_Const_u8 string){
    return(SCu8(string_interpret_escapes(arena, SCchar(string))));
}

global_const u8 integer_symbols[] = {
    '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F',
};

global_const u8 integer_symbol_reverse[128] = {
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    0xFF,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,0x10,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
};

global_const u8 base64[64] = {
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 
    'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 
    'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 
    '_', '$',
};

global_const u8 base64_reverse[128] = {
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,0x3F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,
    0xFF,0x24,0x25,0x26,0x27,0x28,0x29,0x2A,0x2B,0x2C,0x2D,0x2E,0x2F,0x30,0x31,0x32,
    0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3A,0x3B,0x3C,0x3D,0xFF,0xFF,0xFF,0xFF,0x3E,
    0xFF,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,
    0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F,0x20,0x21,0x22,0x23,0xFF,0xFF,0xFF,0xFF,0xFF,
};

static umem
digit_count_from_integer(u64 x, u32 radix){
    umem result = {};
    if (radix >= 2 && radix <= 16){
        if (x == 0){
            result = 1;
        }
        else{
            do{
                x /= radix;
                result += 1;
            } while(x > 0);
        }
    }
    return(result);
}

static String_Const_u8
string_from_integer(Arena *arena, u64 x, u32 radix){
    String_Const_u8 result = {};
    if (radix >= 2 && radix <= 16){
        if (x == 0){
            result = string_copy(arena, string_u8_litexpr("0"));
        }
        else{
            u8 string_space[64];
            umem length = 0;
            for (u64 X = x;
                 X > 0;
                 X /= radix, length += 1){
                string_space[length] = integer_symbols[X%radix];
            }
            for (umem j = 0, i = length - 1;
                 j < i;
                 j += 1, i -= 1){
                Swap(u8, string_space[i], string_space[j]);
            }
            result = string_copy(arena, SCu8(string_space, length));
        }
    }
    return(result);
}

static b32
string_is_integer(String_Const_u8 string, u32 radix){
    b32 is_integer = false;
    if (radix <= 16){
        is_integer = true;
        for (umem i = 0; i < string.size; i += 1){
            if (string.str[i] < 128){
                u8 x = integer_symbol_reverse[character_to_upper(string.str[i])];
                if (x >= radix){
                    is_integer = false;
                    break;
                }
            }
            else{
                is_integer = false;
                break;
            }
        }
    }
    return(is_integer);
}

static u64
string_to_integer(String_Const_u8 string, u32 radix){
    u64 x = 0;
    if (radix <= 16){
        for (umem i = 0; i < string.size; i += 1){
            x *= radix;
            if (string.str[i] < 128){
                x += integer_symbol_reverse[character_to_upper(string.str[i])];
            }
            else{
                x += 0xFF;
            }
        }
    }
    return(x);
}

static u64
string_to_integer(String_Const_char string, u32 radix){
    return(string_to_integer(SCu8((u8*)string.str, string.size), radix));
}

static String_Const_u8
string_base64_encode_from_binary(Arena *arena, void *data, umem size){
    umem char_count = div_round_up_positive(size*8, 6);
    char_count = round_up_umem(char_count, 4);
    String_Const_u8 string = string_const_u8_push(arena, char_count);
    u8 *s = string.str;
    u8 *d = (u8*)data;
    u8 *de = d + size;
    for (;d < de; d += 3, s += 4){
        i32 in_byte_count = (i32)(de - d);
        u8 *D = d;
        b32 partial_fill = (in_byte_count < 3);
        u8 D_space[3] = {};
        if (partial_fill){
            block_copy(D_space, d, clamp_top(sizeof(D_space), in_byte_count));
            D = D_space;
        }
        s[0] =   D[0]      &bitmask_6;
        s[1] = ((D[0] >> 6)&bitmask_2) | ((D[1]&bitmask_4) << 2);
        s[2] = ((D[1] >> 4)&bitmask_4) | ((D[2]&bitmask_2) << 4);
        s[3] =  (D[2] >> 2)&bitmask_6;
        for (i32 j = 0; j < 4; j += 1){
            s[j] = base64[s[j]];
        }
        switch (in_byte_count){
            case 1:
            {
                s[2] = '?';
                s[3] = '?';
            }break;
            case 2:
            {
                s[3] = '?';
            }break;
        }
    }
    return(string);
}

static Data
data_decode_from_base64(Arena *arena, u8 *str, umem size){
    Data data = {};
    if (size%4 == 0){
        umem data_size = size*6/8;
        if (str[size - 2] == '?'){
            data_size -= 2;
        }
        else if (str[size - 1] == '?'){
            data_size -= 1;
        }
        data = push_data(arena, data_size);
        u8 *s = str;
        u8 *se = s + size;
        u8 *d = (u8*)data.data;
        u8 *de = d + data_size;
        for (;s < se; d += 3, s += 4){
            u8 *D = d;
            i32 out_byte_count = (i32)(de - d);
            b32 partial_fill = (out_byte_count < 3);
            u8 D_space[2];
            if (partial_fill){
                D = D_space;
            }
            u8 S[4];
            for (i32 j = 0; j < 4; j += 1){
                if (s[j] < 128){
                    S[j] = base64_reverse[s[j]];
                }
                else{
                    S[j] = 0xFF;
                }
            }
            D[0] = ( S[0]      &bitmask_6) | ((S[1]&bitmask_2) << 6);
            D[1] = ((S[1] >> 2)&bitmask_4) | ((S[2]&bitmask_4) << 4);
            D[2] = ((S[2] >> 4)&bitmask_2) | ((S[3]&bitmask_6) << 2);
            if (partial_fill){
                Assert(out_byte_count <= sizeof(D_space));
                block_copy(D, D_space, out_byte_count);
            }
        }
    }
    return(data);
}

#endif

////////////////////////////////

#if defined(FSTRING_GUARD)
static String
string_old_from_new(String_Const_char string){
    return(make_string(string.str, (i32)string.size));
}
static String
string_old_from_new(String_Const_u8 string){
    return(make_string((char*)string.str, (i32)string.size));
}
static String_Const_char
string_new_from_old(String string){
    return(SCchar(string.str, (umem)string.size));
}
static String_Const_u8
string_new_u8_from_old(String string){
    return(SCu8((u8*)string.str, (umem)string.size));
}
#endif

#endif

// BOTTOM
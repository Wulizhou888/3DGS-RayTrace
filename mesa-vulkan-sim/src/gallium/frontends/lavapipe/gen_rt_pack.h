#ifndef GEN_PACK_H
#define GEN_PACK_H

union __gen_value {
   float f;
   uint32_t dw;
};

#ifndef __gen_validate_value
#define __gen_validate_value(x)
#endif

static inline __attribute__((always_inline)) uint32_t
__gen_float(float v)
{
   __gen_validate_value(v);
   return ((union __gen_value) { .f = (v) }).dw;
}

static inline __attribute__((always_inline)) uint64_t
__gen_offset(uint64_t v, uint32_t start, uint32_t end)
{
   __gen_validate_value(v);
   return v;
}

static inline __attribute__((always_inline)) uint64_t
__gen_sint(int64_t v, uint32_t start, uint32_t end)
{
   const int width = end - start + 1;
   __gen_validate_value(v);
   const uint64_t mask = ~0ull >> (64 - width);
   return (v & mask) << start;
}

static inline __attribute__((always_inline)) uint64_t
__gen_uint(uint64_t v, uint32_t start, uint32_t end)
{
   __gen_validate_value(v);
   return v << start;
}

static inline uint64_t
__gen_combine_address(struct anv_batch *batch, void *location,
                     const struct anv_address address, uint32_t delta)
{
   if (address.bo == NULL)
      return address.offset + delta;

   if (batch)
      anv_reloc_list_add_bo(batch->relocs, batch->alloc, address.bo);

   return anv_address_physical(anv_address_add(address, delta));
}

static inline __attribute__((always_inline)) uint64_t
__gen_address(struct anv_batch *data, void *location,
              struct anv_address address, uint32_t delta,
              uint32_t start, uint32_t end)
{
   uint64_t addr_u64 = __gen_combine_address(data, location, address, delta);
   if (end == 31) {
      assert(addr_u64 <= UINT32_MAX);
      return addr_u64;
   } else if (end < 63) {
      const unsigned shift = 63 - end;
      return (addr_u64 << shift) >> shift;
   } else {
      return addr_u64;
   }
}
// #define GEN_BINDLESS_SHADER_RECORD_length      2
// struct GEN_BINDLESS_SHADER_RECORD {
//    uint32_t                             OffsetToLocalArguments;
//    uint32_t                             BindlessShaderDispatchMode;
// #define SIMD8                                    0
// #define SIMD16                                   1
//    uint64_t                             KernelStartPointer;
// };

// static inline __attribute__((always_inline)) void
// GEN_BINDLESS_SHADER_RECORD_pack(__attribute__((unused)) struct anv_batch *data,
//                                 __attribute__((unused)) void * restrict dst,
//                                 __attribute__((unused)) const struct GEN_BINDLESS_SHADER_RECORD * restrict values)
// {
//    uint32_t * restrict dw = (uint32_t * restrict) dst;

//    dw[0] =
//       __gen_uint(values->OffsetToLocalArguments, 0, 2) |
//       __gen_uint(values->BindlessShaderDispatchMode, 4, 4) |
//       __gen_offset(values->KernelStartPointer, 6, 31);

//    dw[1] = 0;
// }

// #define GEN_RT_GENERAL_SBT_HANDLE_length       8
// struct GEN_RT_GENERAL_SBT_HANDLE {
//    struct GEN_BINDLESS_SHADER_RECORD    General;
// };

// static inline __attribute__((always_inline)) void
// GEN_RT_GENERAL_SBT_HANDLE_pack(__attribute__((unused)) struct anv_batch *data,
//                                __attribute__((unused)) void * restrict dst,
//                                __attribute__((unused)) const struct GEN_RT_GENERAL_SBT_HANDLE * restrict values)
// {
//    uint32_t * restrict dw = (uint32_t * restrict) dst;

//    GEN_BINDLESS_SHADER_RECORD_pack(data, &dw[0], &values->General);

//    dw[2] = 0;

//    dw[3] = 0;

//    dw[4] = 0;

//    dw[5] = 0;

//    dw[6] = 0;

//    dw[7] = 0;
// }

// #define GEN_RT_TRIANGLES_SBT_HANDLE_length      8
// struct GEN_RT_TRIANGLES_SBT_HANDLE {
//    struct GEN_BINDLESS_SHADER_RECORD    ClosestHit;
//    struct GEN_BINDLESS_SHADER_RECORD    AnyHit;
// };

// static inline __attribute__((always_inline)) void
// GEN_RT_TRIANGLES_SBT_HANDLE_pack(__attribute__((unused)) struct anv_batch *data,
//                                  __attribute__((unused)) void * restrict dst,
//                                  __attribute__((unused)) const struct GEN_RT_TRIANGLES_SBT_HANDLE * restrict values)
// {
//    uint32_t * restrict dw = (uint32_t * restrict) dst;

//    GEN_BINDLESS_SHADER_RECORD_pack(data, &dw[0], &values->ClosestHit);

//    GEN_BINDLESS_SHADER_RECORD_pack(data, &dw[2], &values->AnyHit);

//    dw[4] = 0;

//    dw[5] = 0;

//    dw[6] = 0;

//    dw[7] = 0;
// }

// #define GEN_RT_PROCEDURAL_SBT_HANDLE_length      8
// struct GEN_RT_PROCEDURAL_SBT_HANDLE {
//    struct GEN_BINDLESS_SHADER_RECORD    ClosestHit;
//    struct GEN_BINDLESS_SHADER_RECORD    Intersection;
// };

// static inline __attribute__((always_inline)) void
// GEN_RT_PROCEDURAL_SBT_HANDLE_pack(__attribute__((unused)) struct anv_batch *data,
//                                   __attribute__((unused)) void * restrict dst,
//                                   __attribute__((unused)) const struct GEN_RT_PROCEDURAL_SBT_HANDLE * restrict values)
// {
//    uint32_t * restrict dw = (uint32_t * restrict) dst;

//    GEN_BINDLESS_SHADER_RECORD_pack(data, &dw[0], &values->ClosestHit);

//    GEN_BINDLESS_SHADER_RECORD_pack(data, &dw[2], &values->Intersection);

//    dw[4] = 0;

//    dw[5] = 0;

//    dw[6] = 0;

//    dw[7] = 0;
// }

// #define GEN_RT_SHADER_TABLE_length             2
// struct GEN_RT_SHADER_TABLE {
//    struct anv_address                   BaseAddress;
//    uint32_t                             Stride;
// };

// static inline __attribute__((always_inline)) void
// GEN_RT_SHADER_TABLE_pack(__attribute__((unused)) struct anv_batch *data,
//                          __attribute__((unused)) void * restrict dst,
//                          __attribute__((unused)) const struct GEN_RT_SHADER_TABLE * restrict values)
// {
//    uint32_t * restrict dw = (uint32_t * restrict) dst;

//    const uint64_t v0 =
//       __gen_uint(values->Stride, 48, 63);
//    const uint64_t v0_address =
//       __gen_address(data, &dw[0], values->BaseAddress, v0, 0, 47);
//    dw[0] = v0_address;
//    dw[1] = (v0_address >> 32) | (v0 >> 32);
// }

// #define GEN_RT_DISPATCH_GLOBALS_length        20
// struct GEN_RT_DISPATCH_GLOBALS {
//    struct anv_address                   MemBaseAddress;
//    struct GEN_BINDLESS_SHADER_RECORD    CallStackHandler;
//    uint32_t                             AsyncRTStackSize;
//    uint32_t                             NumDSSRTStacks;
//    uint32_t                             MaxBVHLevels;
//    uint32_t                             Flags;
// #define RT_DEPTH_TEST_LESS_EQUAL                 1
//    struct GEN_RT_SHADER_TABLE           HitGroupTable;
//    struct GEN_RT_SHADER_TABLE           MissGroupTable;
//    uint32_t                             SWStackSize;
//    uint32_t                             LaunchWidth;
//    uint32_t                             LaunchHeight;
//    uint32_t                             LaunchDepth;
//    struct GEN_RT_SHADER_TABLE           CallableGroupTable;
//    struct anv_address                   ResumeShaderTable;
// };

// static inline __attribute__((always_inline)) void
// GEN_RT_DISPATCH_GLOBALS_pack(__attribute__((unused)) struct anv_batch *data,
//                              __attribute__((unused)) void * restrict dst,
//                              __attribute__((unused)) const struct GEN_RT_DISPATCH_GLOBALS * restrict values)
// {
//    uint32_t * restrict dw = (uint32_t * restrict) dst;

//    const uint64_t v0_address =
//       __gen_address(data, &dw[0], values->MemBaseAddress, 0, 0, 63);
//    dw[0] = v0_address;
//    dw[1] = v0_address >> 32;

//    GEN_BINDLESS_SHADER_RECORD_pack(data, &dw[2], &values->CallStackHandler);

//    dw[4] =
//       __gen_uint(values->AsyncRTStackSize, 0, 31);

//    dw[5] =
//       __gen_uint(values->NumDSSRTStacks, 0, 15);

//    dw[6] =
//       __gen_uint(values->MaxBVHLevels, 0, 2);

//    dw[7] =
//       __gen_uint(values->Flags, 0, 0);

//    GEN_RT_SHADER_TABLE_pack(data, &dw[8], &values->HitGroupTable);

//    GEN_RT_SHADER_TABLE_pack(data, &dw[10], &values->MissGroupTable);

//    dw[12] =
//       __gen_uint(values->SWStackSize, 0, 31);

//    dw[13] =
//       __gen_uint(values->LaunchWidth, 0, 31);

//    dw[14] =
//       __gen_uint(values->LaunchHeight, 0, 31);

//    dw[15] =
//       __gen_uint(values->LaunchDepth, 0, 31);

//    GEN_RT_SHADER_TABLE_pack(data, &dw[16], &values->CallableGroupTable);

//    const uint64_t v18_address =
//       __gen_address(data, &dw[18], values->ResumeShaderTable, 0, 0, 63);
//    dw[18] = v18_address;
//    dw[19] = v18_address >> 32;
// }

#define GEN_RT_BVH_VEC3_length                 3
struct GEN_RT_BVH_VEC3 {
   float                                X;
   float                                Y;
   float                                Z;
};

static inline __attribute__((always_inline)) void
GEN_RT_BVH_VEC3_pack(__attribute__((unused)) struct anv_batch *data,
                     __attribute__((unused)) void * restrict dst,
                     __attribute__((unused)) const struct GEN_RT_BVH_VEC3 * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      __gen_float(values->X);

   dw[1] =
      __gen_float(values->Y);

   dw[2] =
      __gen_float(values->Z);
}

#define GEN_RT_BVH_length                     16
struct GEN_RT_BVH {
   uint64_t                             RootNodeOffset;
   struct GEN_RT_BVH_VEC3               BoundsMin;
   struct GEN_RT_BVH_VEC3               BoundsMax;
};

static inline __attribute__((always_inline)) void
GEN_RT_BVH_pack(__attribute__((unused)) struct anv_batch *data,
                __attribute__((unused)) void * restrict dst,
                __attribute__((unused)) const struct GEN_RT_BVH * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   const uint64_t v0 =
      __gen_offset(values->RootNodeOffset, 0, 63);
   dw[0] = v0;
   dw[1] = v0 >> 32;

   GEN_RT_BVH_VEC3_pack(data, &dw[2], &values->BoundsMin);

   GEN_RT_BVH_VEC3_pack(data, &dw[5], &values->BoundsMax);

   dw[8] = 0;

   dw[9] = 0;

   dw[10] = 0;

   dw[11] = 0;

   dw[12] = 0;

   dw[13] = 0;

   dw[14] = 0;

   dw[15] = 0;
}

#define GEN_RT_BVH_INTERNAL_NODE_length       16
struct GEN_RT_BVH_INTERNAL_NODE {
   struct GEN_RT_BVH_VEC3               Origin;
   int32_t                              ChildOffset;
   uint32_t                             NodeType;
#define NODE_TYPE_INTERNAL                       0
#define NODE_TYPE_INSTANCE                       1
#define NODE_TYPE_PROCEDURAL                     3
#define NODE_TYPE_QUAD                           4
#define NODE_TYPE_INVALID                        7
   int32_t                              ChildBoundsExponentX;
   int32_t                              ChildBoundsExponentY;
   int32_t                              ChildBoundsExponentZ;
   uint32_t                             NodeRayMask;
   uint32_t                             ChildSize[6];
   uint32_t                             ChildType[6];
   uint32_t                             StartPrimitive[6];
   uint32_t                             ChildLowerXBound[6];
   uint32_t                             ChildUpperXBound[6];
   uint32_t                             ChildLowerYBound[6];
   uint32_t                             ChildUpperYBound[6];
   uint32_t                             ChildLowerZBound[6];
   uint32_t                             ChildUpperZBound[6];
};

static inline __attribute__((always_inline)) void
GEN_RT_BVH_INTERNAL_NODE_pack(__attribute__((unused)) struct anv_batch *data,
                              __attribute__((unused)) void * restrict dst,
                              __attribute__((unused)) const struct GEN_RT_BVH_INTERNAL_NODE * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   GEN_RT_BVH_VEC3_pack(data, &dw[0], &values->Origin);

   dw[3] =
      __gen_sint(values->ChildOffset, 0, 31);

   dw[4] =
      __gen_uint(values->NodeType, 0, 7) |
      __gen_sint(values->ChildBoundsExponentX, 16, 23) |
      __gen_sint(values->ChildBoundsExponentY, 24, 31);

   dw[5] =
      __gen_sint(values->ChildBoundsExponentZ, 0, 8) |
      __gen_uint(values->NodeRayMask, 8, 15) |
      __gen_uint(values->ChildSize[0], 16, 17) |
      __gen_uint(values->ChildType[0], 18, 21) |
      __gen_uint(values->StartPrimitive[0], 18, 21) |
      __gen_uint(values->ChildSize[1], 24, 25) |
      __gen_uint(values->ChildType[1], 26, 29) |
      __gen_uint(values->StartPrimitive[1], 26, 29);

   dw[6] =
      __gen_uint(values->ChildSize[2], 0, 1) |
      __gen_uint(values->ChildType[2], 2, 5) |
      __gen_uint(values->StartPrimitive[2], 2, 5) |
      __gen_uint(values->ChildSize[3], 8, 9) |
      __gen_uint(values->ChildType[3], 10, 13) |
      __gen_uint(values->StartPrimitive[3], 10, 13) |
      __gen_uint(values->ChildSize[4], 16, 17) |
      __gen_uint(values->ChildType[4], 18, 21) |
      __gen_uint(values->StartPrimitive[4], 18, 21) |
      __gen_uint(values->ChildSize[5], 24, 25) |
      __gen_uint(values->ChildType[5], 26, 29) |
      __gen_uint(values->StartPrimitive[5], 26, 29);

   dw[7] =
      __gen_uint(values->ChildLowerXBound[0], 0, 7) |
      __gen_uint(values->ChildLowerXBound[1], 8, 15) |
      __gen_uint(values->ChildLowerXBound[2], 16, 23) |
      __gen_uint(values->ChildLowerXBound[3], 24, 31);

   dw[8] =
      __gen_uint(values->ChildLowerXBound[4], 0, 7) |
      __gen_uint(values->ChildLowerXBound[5], 8, 15) |
      __gen_uint(values->ChildUpperXBound[0], 16, 23) |
      __gen_uint(values->ChildUpperXBound[1], 24, 31);

   dw[9] =
      __gen_uint(values->ChildUpperXBound[2], 0, 7) |
      __gen_uint(values->ChildUpperXBound[3], 8, 15) |
      __gen_uint(values->ChildUpperXBound[4], 16, 23) |
      __gen_uint(values->ChildUpperXBound[5], 24, 31);

   dw[10] =
      __gen_uint(values->ChildLowerYBound[0], 0, 7) |
      __gen_uint(values->ChildLowerYBound[1], 8, 15) |
      __gen_uint(values->ChildLowerYBound[2], 16, 23) |
      __gen_uint(values->ChildLowerYBound[3], 24, 31);

   dw[11] =
      __gen_uint(values->ChildLowerYBound[4], 0, 7) |
      __gen_uint(values->ChildLowerYBound[5], 8, 15) |
      __gen_uint(values->ChildUpperYBound[0], 16, 23) |
      __gen_uint(values->ChildUpperYBound[1], 24, 31);

   dw[12] =
      __gen_uint(values->ChildUpperYBound[2], 0, 7) |
      __gen_uint(values->ChildUpperYBound[3], 8, 15) |
      __gen_uint(values->ChildUpperYBound[4], 16, 23) |
      __gen_uint(values->ChildUpperYBound[5], 24, 31);

   dw[13] =
      __gen_uint(values->ChildLowerZBound[0], 0, 7) |
      __gen_uint(values->ChildLowerZBound[1], 8, 15) |
      __gen_uint(values->ChildLowerZBound[2], 16, 23) |
      __gen_uint(values->ChildLowerZBound[3], 24, 31);

   dw[14] =
      __gen_uint(values->ChildLowerZBound[4], 0, 7) |
      __gen_uint(values->ChildLowerZBound[5], 8, 15) |
      __gen_uint(values->ChildUpperZBound[0], 16, 23) |
      __gen_uint(values->ChildUpperZBound[1], 24, 31);

   dw[15] =
      __gen_uint(values->ChildUpperZBound[2], 0, 7) |
      __gen_uint(values->ChildUpperZBound[3], 8, 15) |
      __gen_uint(values->ChildUpperZBound[4], 16, 23) |
      __gen_uint(values->ChildUpperZBound[5], 24, 31);
}

#define GEN_RT_BVH_PRIMITIVE_LEAF_DESCRIPTOR_length      2
struct GEN_RT_BVH_PRIMITIVE_LEAF_DESCRIPTOR {
   uint32_t                             ShaderIndex;
   uint32_t                             GeometryRayMask;
   uint32_t                             GeometryIndex;
   uint32_t                             LeafType;
#define TYPE_QUAD                                0
#define TYPE_OPAQUE_CULLING_ENABLED              0
#define TYPE_OPAQUE_CULLING_DISABLED             1
#define TYPE_GAUSS                               2  // WLZ
   uint32_t                             GeometryFlags;
#define GEOMETRY_OPAQUE                          1
};

static inline __attribute__((always_inline)) void
GEN_RT_BVH_PRIMITIVE_LEAF_DESCRIPTOR_pack(__attribute__((unused)) struct anv_batch *data,
                                          __attribute__((unused)) void * restrict dst,
                                          __attribute__((unused)) const struct GEN_RT_BVH_PRIMITIVE_LEAF_DESCRIPTOR * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      __gen_uint(values->ShaderIndex, 0, 23) |
      __gen_uint(values->GeometryRayMask, 24, 31);

   dw[1] =
      __gen_uint(values->GeometryIndex, 0, 28) |
      __gen_uint(values->LeafType, 29, 29) |
      __gen_uint(values->GeometryFlags, 30, 31);
}

#define GEN_RT_BVH_QUAD_LEAF_length           16
struct GEN_RT_BVH_QUAD_LEAF {
   struct GEN_RT_BVH_PRIMITIVE_LEAF_DESCRIPTOR LeafDescriptor;
   uint32_t                             PrimitiveIndex0;
   uint32_t                             PrimitiveIndex1Delta;
   uint32_t                             j0;
   uint32_t                             j1;
   uint32_t                             j2;
   bool                                 LastQuad;
   struct GEN_RT_BVH_VEC3               QuadVertex[4];
};

static inline __attribute__((always_inline)) void
GEN_RT_BVH_QUAD_LEAF_pack(__attribute__((unused)) struct anv_batch *data,
                          __attribute__((unused)) void * restrict dst,
                          __attribute__((unused)) const struct GEN_RT_BVH_QUAD_LEAF * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   GEN_RT_BVH_PRIMITIVE_LEAF_DESCRIPTOR_pack(data, &dw[0], &values->LeafDescriptor);

   dw[2] =
      __gen_uint(values->PrimitiveIndex0, 0, 31);

   dw[3] =
      __gen_uint(values->PrimitiveIndex1Delta, 0, 16) |
      __gen_uint(values->j0, 16, 17) |
      __gen_uint(values->j1, 18, 19) |
      __gen_uint(values->j2, 20, 21) |
      __gen_uint(values->LastQuad, 22, 22);

   GEN_RT_BVH_VEC3_pack(data, &dw[4], &values->QuadVertex[0]);

   GEN_RT_BVH_VEC3_pack(data, &dw[7], &values->QuadVertex[1]);

   GEN_RT_BVH_VEC3_pack(data, &dw[10], &values->QuadVertex[2]);

   GEN_RT_BVH_VEC3_pack(data, &dw[13], &values->QuadVertex[3]);
}

#define GEN_RT_BVH_INSTANCE_LEAF_length       32
struct GEN_RT_BVH_INSTANCE_LEAF {
   uint32_t                             ShaderIndex;
   uint32_t                             GeometryRayMask;
   uint32_t                             InstanceContributionToHitGroupIndex;
   uint32_t                             LeafType;
#define TYPE_OPAQUE_CULLING_ENABLED              0
#define TYPE_OPAQUE_CULLING_DISABLED             1
#define TYPE_GAUSS                               2  // WLZ
   uint32_t                             GeometryFlags;
#define GEOMETRY_OPAQUE                          1
   struct anv_address                   StartNodeAddress;
   uint32_t                             InstanceFlags;
#define TRIANGLE_CULL_DISABLE                    1
#define TRIANGLE_FRONT_COUNTERCLOCKWISE          2
#define FORCE_OPAQUE                             4
#define FORCE_NON_OPAQUE                         8
   float                                WorldToObjectm00;
   float                                WorldToObjectm01;
   float                                WorldToObjectm02;
   float                                WorldToObjectm10;
   float                                WorldToObjectm11;
   float                                WorldToObjectm12;
   float                                WorldToObjectm20;
   float                                WorldToObjectm21;
   float                                WorldToObjectm22;
   float                                ObjectToWorldm30;
   float                                ObjectToWorldm31;
   float                                ObjectToWorldm32;
   struct anv_address                   BVHAddress;
   uint32_t                             InstanceID;
   uint32_t                             InstanceIndex;
   float                                ObjectToWorldm00;
   float                                ObjectToWorldm01;
   float                                ObjectToWorldm02;
   float                                ObjectToWorldm10;
   float                                ObjectToWorldm11;
   float                                ObjectToWorldm12;
   float                                ObjectToWorldm20;
   float                                ObjectToWorldm21;
   float                                ObjectToWorldm22;
   float                                WorldToObjectm30;
   float                                WorldToObjectm31;
   float                                WorldToObjectm32;
};

static inline __attribute__((always_inline)) void
GEN_RT_BVH_INSTANCE_LEAF_pack(__attribute__((unused)) struct anv_batch *data,
                              __attribute__((unused)) void * restrict dst,
                              __attribute__((unused)) const struct GEN_RT_BVH_INSTANCE_LEAF * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   dw[0] =
      __gen_uint(values->ShaderIndex, 0, 23) |
      __gen_uint(values->GeometryRayMask, 24, 31);

   dw[1] =
      __gen_uint(values->InstanceContributionToHitGroupIndex, 0, 23) |
      __gen_uint(values->LeafType, 29, 29) |
      __gen_uint(values->GeometryFlags, 30, 31);

   const uint64_t v2 =
      __gen_uint(values->InstanceFlags, 48, 55);
   const uint64_t v2_address =
      __gen_address(data, &dw[2], values->StartNodeAddress, v2, 0, 47);
   dw[2] = v2_address;
   dw[3] = (v2_address >> 32) | (v2 >> 32);

   dw[4] =
      __gen_float(values->WorldToObjectm00);

   dw[5] =
      __gen_float(values->WorldToObjectm01);

   dw[6] =
      __gen_float(values->WorldToObjectm02);

   dw[7] =
      __gen_float(values->WorldToObjectm10);

   dw[8] =
      __gen_float(values->WorldToObjectm11);

   dw[9] =
      __gen_float(values->WorldToObjectm12);

   dw[10] =
      __gen_float(values->WorldToObjectm20);

   dw[11] =
      __gen_float(values->WorldToObjectm21);

   dw[12] =
      __gen_float(values->WorldToObjectm22);

   dw[13] =
      __gen_float(values->ObjectToWorldm30);

   dw[14] =
      __gen_float(values->ObjectToWorldm31);

   dw[15] =
      __gen_float(values->ObjectToWorldm32);

   const uint64_t v16_address =
      __gen_address(data, &dw[16], values->BVHAddress, 0, 0, 63);
   dw[16] = v16_address;
   dw[17] = v16_address >> 32;

   dw[18] =
      __gen_uint(values->InstanceID, 0, 31);

   dw[19] =
      __gen_uint(values->InstanceIndex, 0, 31);

   dw[20] =
      __gen_float(values->ObjectToWorldm00);

   dw[21] =
      __gen_float(values->ObjectToWorldm01);

   dw[22] =
      __gen_float(values->ObjectToWorldm02);

   dw[23] =
      __gen_float(values->ObjectToWorldm10);

   dw[24] =
      __gen_float(values->ObjectToWorldm11);

   dw[25] =
      __gen_float(values->ObjectToWorldm12);

   dw[26] =
      __gen_float(values->ObjectToWorldm20);

   dw[27] =
      __gen_float(values->ObjectToWorldm21);

   dw[28] =
      __gen_float(values->ObjectToWorldm22);

   dw[29] =
      __gen_float(values->WorldToObjectm30);

   dw[30] =
      __gen_float(values->WorldToObjectm31);

   dw[31] =
      __gen_float(values->WorldToObjectm32);
}

#define GEN_RT_BVH_PROCEDURAL_LEAF_length     16
struct GEN_RT_BVH_PROCEDURAL_LEAF {
   struct GEN_RT_BVH_PRIMITIVE_LEAF_DESCRIPTOR LeafDescriptor;
   uint32_t                             NumPrimitives;
   uint32_t                             LastPrimitive;
   uint32_t                             PrimitiveIndex[13];
};

static inline __attribute__((always_inline)) void
GEN_RT_BVH_PROCEDURAL_LEAF_pack(__attribute__((unused)) struct anv_batch *data,
                                __attribute__((unused)) void * restrict dst,
                                __attribute__((unused)) const struct GEN_RT_BVH_PROCEDURAL_LEAF * restrict values)
{
   uint32_t * restrict dw = (uint32_t * restrict) dst;

   GEN_RT_BVH_PRIMITIVE_LEAF_DESCRIPTOR_pack(data, &dw[0], &values->LeafDescriptor);

   dw[2] =
      __gen_uint(values->NumPrimitives, 0, 3) |
      __gen_uint(values->LastPrimitive, 19, 31);

   dw[3] =
      __gen_uint(values->PrimitiveIndex[0], 0, 31);

   dw[4] =
      __gen_uint(values->PrimitiveIndex[1], 0, 31);

   dw[5] =
      __gen_uint(values->PrimitiveIndex[2], 0, 31);

   dw[6] =
      __gen_uint(values->PrimitiveIndex[3], 0, 31);

   dw[7] =
      __gen_uint(values->PrimitiveIndex[4], 0, 31);

   dw[8] =
      __gen_uint(values->PrimitiveIndex[5], 0, 31);

   dw[9] =
      __gen_uint(values->PrimitiveIndex[6], 0, 31);

   dw[10] =
      __gen_uint(values->PrimitiveIndex[7], 0, 31);

   dw[11] =
      __gen_uint(values->PrimitiveIndex[8], 0, 31);

   dw[12] =
      __gen_uint(values->PrimitiveIndex[9], 0, 31);

   dw[13] =
      __gen_uint(values->PrimitiveIndex[10], 0, 31);

   dw[14] =
      __gen_uint(values->PrimitiveIndex[11], 0, 31);

   dw[15] =
      __gen_uint(values->PrimitiveIndex[12], 0, 31);
}


#endif /* GEN_PACK_H */

// Generated with `xb buildshaders`.
#if 0
; SPIR-V
; Version: 1.0
; Generator: Khronos Glslang Reference Front End; 11
; Bound: 24500
; Schema: 0
               OpCapability Tessellation
          %1 = OpExtInstImport "GLSL.std.450"
               OpMemoryModel Logical GLSL450
               OpEntryPoint TessellationControl %main "main" %gl_TessLevelOuter %in_edge_factor %gl_TessLevelInner %out_index %gl_InvocationID %gl_PrimitiveID
               OpExecutionMode %main OutputVertices 1
               OpSource GLSL 460
               OpSourceExtension "GL_GOOGLE_cpp_style_line_directive"
               OpSourceExtension "GL_GOOGLE_include_directive"
               OpName %main "main"
               OpName %gl_TessLevelOuter "gl_TessLevelOuter"
               OpName %in_edge_factor "in_edge_factor"
               OpName %gl_TessLevelInner "gl_TessLevelInner"
               OpName %out_index "out_index"
               OpName %gl_InvocationID "gl_InvocationID"
               OpName %gl_PrimitiveID "gl_PrimitiveID"
               OpName %XeTessellationConstants "XeTessellationConstants"
               OpMemberName %XeTessellationConstants 0 "xe_tessellation_factor_range"
               OpMemberName %XeTessellationConstants 1 "xe_tessellation_padding0"
               OpMemberName %XeTessellationConstants 2 "xe_vertex_index_endian"
               OpMemberName %XeTessellationConstants 3 "xe_vertex_index_offset"
               OpMemberName %XeTessellationConstants 4 "xe_vertex_index_min_max"
               OpName %_ ""
               OpDecorate %gl_TessLevelOuter BuiltIn TessLevelOuter
               OpDecorate %gl_TessLevelOuter Patch
               OpDecorate %in_edge_factor Location 0
               OpDecorate %gl_TessLevelInner BuiltIn TessLevelInner
               OpDecorate %gl_TessLevelInner Patch
               OpDecorate %out_index Location 0
               OpDecorate %gl_InvocationID BuiltIn InvocationId
               OpDecorate %gl_PrimitiveID BuiltIn PrimitiveId
               OpDecorate %XeTessellationConstants Block
               OpMemberDecorate %XeTessellationConstants 0 Offset 0
               OpMemberDecorate %XeTessellationConstants 1 Offset 8
               OpMemberDecorate %XeTessellationConstants 2 Offset 16
               OpMemberDecorate %XeTessellationConstants 3 Offset 20
               OpMemberDecorate %XeTessellationConstants 4 Offset 24
               OpDecorate %_ Binding 6
               OpDecorate %_ DescriptorSet 1
       %void = OpTypeVoid
       %1282 = OpTypeFunction %void
      %float = OpTypeFloat 32
       %uint = OpTypeInt 32 0
     %uint_4 = OpConstant %uint 4
%_arr_float_uint_4 = OpTypeArray %float %uint_4
%_ptr_Output__arr_float_uint_4 = OpTypePointer Output %_arr_float_uint_4
%gl_TessLevelOuter = OpVariable %_ptr_Output__arr_float_uint_4 Output
        %int = OpTypeInt 32 1
      %int_0 = OpConstant %int 0
    %uint_32 = OpConstant %uint 32
%_arr_float_uint_32 = OpTypeArray %float %uint_32
%_ptr_Input__arr_float_uint_32 = OpTypePointer Input %_arr_float_uint_32
%in_edge_factor = OpVariable %_ptr_Input__arr_float_uint_32 Input
      %int_3 = OpConstant %int 3
%_ptr_Input_float = OpTypePointer Input %float
%_ptr_Output_float = OpTypePointer Output %float
      %int_1 = OpConstant %int 1
      %int_2 = OpConstant %int 2
     %uint_2 = OpConstant %uint 2
%_arr_float_uint_2 = OpTypeArray %float %uint_2
%_ptr_Output__arr_float_uint_2 = OpTypePointer Output %_arr_float_uint_2
%gl_TessLevelInner = OpVariable %_ptr_Output__arr_float_uint_2 Output
     %uint_1 = OpConstant %uint 1
%_arr_float_uint_1 = OpTypeArray %float %uint_1
%_ptr_Output__arr_float_uint_1 = OpTypePointer Output %_arr_float_uint_1
  %out_index = OpVariable %_ptr_Output__arr_float_uint_1 Output
%_ptr_Input_int = OpTypePointer Input %int
%gl_InvocationID = OpVariable %_ptr_Input_int Input
%gl_PrimitiveID = OpVariable %_ptr_Input_int Input
    %v2float = OpTypeVector %float 2
     %v2uint = OpTypeVector %uint 2
%XeTessellationConstants = OpTypeStruct %v2float %v2float %uint %uint %v2uint
%_ptr_Uniform_XeTessellationConstants = OpTypePointer Uniform %XeTessellationConstants
          %_ = OpVariable %_ptr_Uniform_XeTessellationConstants Uniform
%_ptr_Uniform_uint = OpTypePointer Uniform %uint
%uint_16777215 = OpConstant %uint 16777215
      %int_4 = OpConstant %int 4
     %uint_0 = OpConstant %uint 0
       %main = OpFunction %void None %1282
      %23915 = OpLabel
       %7129 = OpAccessChain %_ptr_Input_float %in_edge_factor %int_3
      %15646 = OpLoad %float %7129
      %19981 = OpAccessChain %_ptr_Output_float %gl_TessLevelOuter %int_0
               OpStore %19981 %15646
      %19905 = OpAccessChain %_ptr_Input_float %in_edge_factor %int_0
       %7391 = OpLoad %float %19905
      %19982 = OpAccessChain %_ptr_Output_float %gl_TessLevelOuter %int_1
               OpStore %19982 %7391
      %19906 = OpAccessChain %_ptr_Input_float %in_edge_factor %int_1
       %7392 = OpLoad %float %19906
      %19983 = OpAccessChain %_ptr_Output_float %gl_TessLevelOuter %int_2
               OpStore %19983 %7392
      %19907 = OpAccessChain %_ptr_Input_float %in_edge_factor %int_2
       %7393 = OpLoad %float %19907
      %19908 = OpAccessChain %_ptr_Output_float %gl_TessLevelOuter %int_3
               OpStore %19908 %7393
      %13565 = OpLoad %float %19982
      %12692 = OpLoad %float %19908
       %7944 = OpExtInst %float %1 FMin %13565 %12692
      %14721 = OpAccessChain %_ptr_Output_float %gl_TessLevelInner %int_0
               OpStore %14721 %7944
      %13566 = OpLoad %float %19981
      %12693 = OpLoad %float %19983
       %7945 = OpExtInst %float %1 FMin %13566 %12693
      %14722 = OpAccessChain %_ptr_Output_float %gl_TessLevelInner %int_1
               OpStore %14722 %7945
      %15656 = OpLoad %int %gl_InvocationID
      %23765 = OpLoad %int %gl_PrimitiveID
       %9548 = OpBitcast %uint %23765
       %7395 = OpAccessChain %_ptr_Uniform_uint %_ %int_3
      %22970 = OpLoad %uint %7395
       %7652 = OpIAdd %uint %9548 %22970
      %18847 = OpBitwiseAnd %uint %7652 %uint_16777215
      %10702 = OpAccessChain %_ptr_Uniform_uint %_ %int_4 %uint_0
      %24236 = OpLoad %uint %10702
      %19191 = OpAccessChain %_ptr_Uniform_uint %_ %int_4 %uint_1
      %22108 = OpLoad %uint %19191
      %23780 = OpExtInst %uint %1 UClamp %18847 %24236 %22108
      %24499 = OpConvertUToF %float %23780
      %12694 = OpAccessChain %_ptr_Output_float %out_index %15656
               OpStore %12694 %24499
               OpReturn
               OpFunctionEnd
#endif

const uint32_t adaptive_quad_hs[] = {
    0x07230203, 0x00010000, 0x0008000B, 0x00005FB4, 0x00000000, 0x00020011,
    0x00000003, 0x0006000B, 0x00000001, 0x4C534C47, 0x6474732E, 0x3035342E,
    0x00000000, 0x0003000E, 0x00000000, 0x00000001, 0x000B000F, 0x00000001,
    0x0000161F, 0x6E69616D, 0x00000000, 0x00001548, 0x00001093, 0x00000CDA,
    0x00000CEB, 0x000011E9, 0x000014CB, 0x00040010, 0x0000161F, 0x0000001A,
    0x00000001, 0x00030003, 0x00000002, 0x000001CC, 0x000A0004, 0x475F4C47,
    0x4C474F4F, 0x70635F45, 0x74735F70, 0x5F656C79, 0x656E696C, 0x7269645F,
    0x69746365, 0x00006576, 0x00080004, 0x475F4C47, 0x4C474F4F, 0x6E695F45,
    0x64756C63, 0x69645F65, 0x74636572, 0x00657669, 0x00040005, 0x0000161F,
    0x6E69616D, 0x00000000, 0x00070005, 0x00001548, 0x545F6C67, 0x4C737365,
    0x6C657665, 0x6574754F, 0x00000072, 0x00060005, 0x00001093, 0x655F6E69,
    0x5F656764, 0x74636166, 0x0000726F, 0x00070005, 0x00000CDA, 0x545F6C67,
    0x4C737365, 0x6C657665, 0x656E6E49, 0x00000072, 0x00050005, 0x00000CEB,
    0x5F74756F, 0x65646E69, 0x00000078, 0x00060005, 0x000011E9, 0x495F6C67,
    0x636F766E, 0x6F697461, 0x0044496E, 0x00060005, 0x000014CB, 0x505F6C67,
    0x696D6972, 0x65766974, 0x00004449, 0x00080005, 0x00000457, 0x65546558,
    0x6C657373, 0x6974616C, 0x6F436E6F, 0x6174736E, 0x0073746E, 0x000B0006,
    0x00000457, 0x00000000, 0x745F6578, 0x65737365, 0x74616C6C, 0x5F6E6F69,
    0x74636166, 0x725F726F, 0x65676E61, 0x00000000, 0x000A0006, 0x00000457,
    0x00000001, 0x745F6578, 0x65737365, 0x74616C6C, 0x5F6E6F69, 0x64646170,
    0x30676E69, 0x00000000, 0x00090006, 0x00000457, 0x00000002, 0x765F6578,
    0x65747265, 0x6E695F78, 0x5F786564, 0x69646E65, 0x00006E61, 0x00090006,
    0x00000457, 0x00000003, 0x765F6578, 0x65747265, 0x6E695F78, 0x5F786564,
    0x7366666F, 0x00007465, 0x00090006, 0x00000457, 0x00000004, 0x765F6578,
    0x65747265, 0x6E695F78, 0x5F786564, 0x5F6E696D, 0x0078616D, 0x00030005,
    0x00001342, 0x00000000, 0x00040047, 0x00001548, 0x0000000B, 0x0000000B,
    0x00030047, 0x00001548, 0x0000000F, 0x00040047, 0x00001093, 0x0000001E,
    0x00000000, 0x00040047, 0x00000CDA, 0x0000000B, 0x0000000C, 0x00030047,
    0x00000CDA, 0x0000000F, 0x00040047, 0x00000CEB, 0x0000001E, 0x00000000,
    0x00040047, 0x000011E9, 0x0000000B, 0x00000008, 0x00040047, 0x000014CB,
    0x0000000B, 0x00000007, 0x00030047, 0x00000457, 0x00000002, 0x00050048,
    0x00000457, 0x00000000, 0x00000023, 0x00000000, 0x00050048, 0x00000457,
    0x00000001, 0x00000023, 0x00000008, 0x00050048, 0x00000457, 0x00000002,
    0x00000023, 0x00000010, 0x00050048, 0x00000457, 0x00000003, 0x00000023,
    0x00000014, 0x00050048, 0x00000457, 0x00000004, 0x00000023, 0x00000018,
    0x00040047, 0x00001342, 0x00000021, 0x00000006, 0x00040047, 0x00001342,
    0x00000022, 0x00000001, 0x00020013, 0x00000008, 0x00030021, 0x00000502,
    0x00000008, 0x00030016, 0x0000000D, 0x00000020, 0x00040015, 0x0000000B,
    0x00000020, 0x00000000, 0x0004002B, 0x0000000B, 0x00000A16, 0x00000004,
    0x0004001C, 0x00000225, 0x0000000D, 0x00000A16, 0x00040020, 0x000004A2,
    0x00000003, 0x00000225, 0x0004003B, 0x000004A2, 0x00001548, 0x00000003,
    0x00040015, 0x0000000C, 0x00000020, 0x00000001, 0x0004002B, 0x0000000C,
    0x00000A0B, 0x00000000, 0x0004002B, 0x0000000B, 0x00000A6A, 0x00000020,
    0x0004001C, 0x00000243, 0x0000000D, 0x00000A6A, 0x00040020, 0x000004C0,
    0x00000001, 0x00000243, 0x0004003B, 0x000004C0, 0x00001093, 0x00000001,
    0x0004002B, 0x0000000C, 0x00000A14, 0x00000003, 0x00040020, 0x0000028A,
    0x00000001, 0x0000000D, 0x00040020, 0x0000028B, 0x00000003, 0x0000000D,
    0x0004002B, 0x0000000C, 0x00000A0E, 0x00000001, 0x0004002B, 0x0000000C,
    0x00000A11, 0x00000002, 0x0004002B, 0x0000000B, 0x00000A10, 0x00000002,
    0x0004001C, 0x000002AC, 0x0000000D, 0x00000A10, 0x00040020, 0x00000529,
    0x00000003, 0x000002AC, 0x0004003B, 0x00000529, 0x00000CDA, 0x00000003,
    0x0004002B, 0x0000000B, 0x00000A0D, 0x00000001, 0x0004001C, 0x000002FC,
    0x0000000D, 0x00000A0D, 0x00040020, 0x00000579, 0x00000003, 0x000002FC,
    0x0004003B, 0x00000579, 0x00000CEB, 0x00000003, 0x00040020, 0x00000289,
    0x00000001, 0x0000000C, 0x0004003B, 0x00000289, 0x000011E9, 0x00000001,
    0x0004003B, 0x00000289, 0x000014CB, 0x00000001, 0x00040017, 0x00000013,
    0x0000000D, 0x00000002, 0x00040017, 0x00000011, 0x0000000B, 0x00000002,
    0x0007001E, 0x00000457, 0x00000013, 0x00000013, 0x0000000B, 0x0000000B,
    0x00000011, 0x00040020, 0x000006D4, 0x00000002, 0x00000457, 0x0004003B,
    0x000006D4, 0x00001342, 0x00000002, 0x00040020, 0x00000288, 0x00000002,
    0x0000000B, 0x0004002B, 0x0000000B, 0x00000923, 0x00FFFFFF, 0x0004002B,
    0x0000000C, 0x00000A17, 0x00000004, 0x0004002B, 0x0000000B, 0x00000A0A,
    0x00000000, 0x00050036, 0x00000008, 0x0000161F, 0x00000000, 0x00000502,
    0x000200F8, 0x00005D6B, 0x00050041, 0x0000028A, 0x00001BD9, 0x00001093,
    0x00000A14, 0x0004003D, 0x0000000D, 0x00003D1E, 0x00001BD9, 0x00050041,
    0x0000028B, 0x00004E0D, 0x00001548, 0x00000A0B, 0x0003003E, 0x00004E0D,
    0x00003D1E, 0x00050041, 0x0000028A, 0x00004DC1, 0x00001093, 0x00000A0B,
    0x0004003D, 0x0000000D, 0x00001CDF, 0x00004DC1, 0x00050041, 0x0000028B,
    0x00004E0E, 0x00001548, 0x00000A0E, 0x0003003E, 0x00004E0E, 0x00001CDF,
    0x00050041, 0x0000028A, 0x00004DC2, 0x00001093, 0x00000A0E, 0x0004003D,
    0x0000000D, 0x00001CE0, 0x00004DC2, 0x00050041, 0x0000028B, 0x00004E0F,
    0x00001548, 0x00000A11, 0x0003003E, 0x00004E0F, 0x00001CE0, 0x00050041,
    0x0000028A, 0x00004DC3, 0x00001093, 0x00000A11, 0x0004003D, 0x0000000D,
    0x00001CE1, 0x00004DC3, 0x00050041, 0x0000028B, 0x00004DC4, 0x00001548,
    0x00000A14, 0x0003003E, 0x00004DC4, 0x00001CE1, 0x0004003D, 0x0000000D,
    0x000034FD, 0x00004E0E, 0x0004003D, 0x0000000D, 0x00003194, 0x00004DC4,
    0x0007000C, 0x0000000D, 0x00001F08, 0x00000001, 0x00000025, 0x000034FD,
    0x00003194, 0x00050041, 0x0000028B, 0x00003981, 0x00000CDA, 0x00000A0B,
    0x0003003E, 0x00003981, 0x00001F08, 0x0004003D, 0x0000000D, 0x000034FE,
    0x00004E0D, 0x0004003D, 0x0000000D, 0x00003195, 0x00004E0F, 0x0007000C,
    0x0000000D, 0x00001F09, 0x00000001, 0x00000025, 0x000034FE, 0x00003195,
    0x00050041, 0x0000028B, 0x00003982, 0x00000CDA, 0x00000A0E, 0x0003003E,
    0x00003982, 0x00001F09, 0x0004003D, 0x0000000C, 0x00003D28, 0x000011E9,
    0x0004003D, 0x0000000C, 0x00005CD5, 0x000014CB, 0x0004007C, 0x0000000B,
    0x0000254C, 0x00005CD5, 0x00050041, 0x00000288, 0x00001CE3, 0x00001342,
    0x00000A14, 0x0004003D, 0x0000000B, 0x000059BA, 0x00001CE3, 0x00050080,
    0x0000000B, 0x00001DE4, 0x0000254C, 0x000059BA, 0x000500C7, 0x0000000B,
    0x0000499F, 0x00001DE4, 0x00000923, 0x00060041, 0x00000288, 0x000029CE,
    0x00001342, 0x00000A17, 0x00000A0A, 0x0004003D, 0x0000000B, 0x00005EAC,
    0x000029CE, 0x00060041, 0x00000288, 0x00004AF7, 0x00001342, 0x00000A17,
    0x00000A0D, 0x0004003D, 0x0000000B, 0x0000565C, 0x00004AF7, 0x0008000C,
    0x0000000B, 0x00005CE4, 0x00000001, 0x0000002C, 0x0000499F, 0x00005EAC,
    0x0000565C, 0x00040070, 0x0000000D, 0x00005FB3, 0x00005CE4, 0x00050041,
    0x0000028B, 0x00003196, 0x00000CEB, 0x00003D28, 0x0003003E, 0x00003196,
    0x00005FB3, 0x000100FD, 0x00010038,
};

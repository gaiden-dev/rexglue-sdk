// Generated with `xb buildshaders`.
#if 0
; SPIR-V
; Version: 1.0
; Generator: Khronos Glslang Reference Front End; 11
; Bound: 25190
; Schema: 0
               OpCapability Shader
          %1 = OpExtInstImport "GLSL.std.450"
               OpMemoryModel Logical GLSL450
               OpEntryPoint GLCompute %main "main" %gl_WorkGroupID %gl_LocalInvocationIndex
               OpExecutionMode %main LocalSize 128 1 1
               OpSource GLSL 460
               OpSourceExtension "GL_EXT_control_flow_attributes"
               OpSourceExtension "GL_EXT_samplerless_texture_functions"
               OpSourceExtension "GL_GOOGLE_cpp_style_line_directive"
               OpSourceExtension "GL_GOOGLE_include_directive"
               OpName %main "main"
               OpName %gl_WorkGroupID "gl_WorkGroupID"
               OpName %push_const_block_xe "push_const_block_xe"
               OpMemberName %push_const_block_xe 0 "xe_downscale_scale_x"
               OpMemberName %push_const_block_xe 1 "xe_downscale_scale_y"
               OpMemberName %push_const_block_xe 2 "xe_downscale_pixel_size_log2"
               OpMemberName %push_const_block_xe 3 "xe_downscale_tile_count"
               OpMemberName %push_const_block_xe 4 "xe_downscale_source_offset_bytes"
               OpMemberName %push_const_block_xe 5 "xe_downscale_half_pixel_offset"
               OpName %push_consts_xe "push_consts_xe"
               OpName %gl_LocalInvocationIndex "gl_LocalInvocationIndex"
               OpName %xe_downscale_dest_xe_block "xe_downscale_dest_xe_block"
               OpMemberName %xe_downscale_dest_xe_block 0 "data"
               OpName %xe_downscale_dest "xe_downscale_dest"
               OpName %xe_downscale_source_xe_block "xe_downscale_source_xe_block"
               OpMemberName %xe_downscale_source_xe_block 0 "data"
               OpName %xe_downscale_source "xe_downscale_source"
               OpDecorate %gl_WorkGroupID BuiltIn WorkgroupId
               OpDecorate %push_const_block_xe Block
               OpMemberDecorate %push_const_block_xe 0 Offset 0
               OpMemberDecorate %push_const_block_xe 1 Offset 4
               OpMemberDecorate %push_const_block_xe 2 Offset 8
               OpMemberDecorate %push_const_block_xe 3 Offset 12
               OpMemberDecorate %push_const_block_xe 4 Offset 16
               OpMemberDecorate %push_const_block_xe 5 Offset 20
               OpDecorate %gl_LocalInvocationIndex BuiltIn LocalInvocationIndex
               OpDecorate %_runtimearr_uint ArrayStride 4
               OpDecorate %xe_downscale_dest_xe_block BufferBlock
               OpMemberDecorate %xe_downscale_dest_xe_block 0 NonReadable
               OpMemberDecorate %xe_downscale_dest_xe_block 0 Offset 0
               OpDecorate %xe_downscale_dest NonReadable
               OpDecorate %xe_downscale_dest Binding 0
               OpDecorate %xe_downscale_dest DescriptorSet 1
               OpDecorate %_runtimearr_uint_0 ArrayStride 4
               OpDecorate %xe_downscale_source_xe_block BufferBlock
               OpMemberDecorate %xe_downscale_source_xe_block 0 NonWritable
               OpMemberDecorate %xe_downscale_source_xe_block 0 Offset 0
               OpDecorate %xe_downscale_source NonWritable
               OpDecorate %xe_downscale_source Binding 0
               OpDecorate %xe_downscale_source DescriptorSet 0
               OpDecorate %gl_WorkGroupSize BuiltIn WorkgroupSize
       %void = OpTypeVoid
       %1282 = OpTypeFunction %void
       %uint = OpTypeInt 32 0
     %uint_2 = OpConstant %uint 2
       %bool = OpTypeBool
     %uint_7 = OpConstant %uint 7
     %uint_6 = OpConstant %uint 6
     %uint_1 = OpConstant %uint 1
     %uint_0 = OpConstant %uint 0
     %uint_3 = OpConstant %uint 3
     %uint_4 = OpConstant %uint 4
     %uint_5 = OpConstant %uint 5
     %v3uint = OpTypeVector %uint 3
%_ptr_Input_v3uint = OpTypePointer Input %v3uint
%gl_WorkGroupID = OpVariable %_ptr_Input_v3uint Input
%_ptr_Input_uint = OpTypePointer Input %uint
%push_const_block_xe = OpTypeStruct %uint %uint %uint %uint %uint %uint
%_ptr_PushConstant_push_const_block_xe = OpTypePointer PushConstant %push_const_block_xe
%push_consts_xe = OpVariable %_ptr_PushConstant_push_const_block_xe PushConstant
        %int = OpTypeInt 32 1
      %int_3 = OpConstant %int 3
%_ptr_PushConstant_uint = OpTypePointer PushConstant %uint
      %int_2 = OpConstant %int 2
      %int_0 = OpConstant %int 0
      %int_1 = OpConstant %int 1
  %uint_1024 = OpConstant %uint 1024
      %int_5 = OpConstant %int 5
      %int_4 = OpConstant %int 4
%gl_LocalInvocationIndex = OpVariable %_ptr_Input_uint Input
%_runtimearr_uint = OpTypeRuntimeArray %uint
%xe_downscale_dest_xe_block = OpTypeStruct %_runtimearr_uint
%_ptr_Uniform_xe_downscale_dest_xe_block = OpTypePointer Uniform %xe_downscale_dest_xe_block
%xe_downscale_dest = OpVariable %_ptr_Uniform_xe_downscale_dest_xe_block Uniform
%_runtimearr_uint_0 = OpTypeRuntimeArray %uint
%xe_downscale_source_xe_block = OpTypeStruct %_runtimearr_uint_0
%_ptr_Uniform_xe_downscale_source_xe_block = OpTypePointer Uniform %xe_downscale_source_xe_block
%xe_downscale_source = OpVariable %_ptr_Uniform_xe_downscale_source_xe_block Uniform
%_ptr_Uniform_uint = OpTypePointer Uniform %uint
     %uint_8 = OpConstant %uint 8
%uint_4294967292 = OpConstant %uint 4294967292
   %uint_128 = OpConstant %uint 128
%gl_WorkGroupSize = OpConstantComposite %v3uint %uint_128 %uint_1 %uint_1
       %main = OpFunction %void None %1282
      %15110 = OpLabel
               OpSelectionMerge %14903 None
               OpSwitch %uint_0 %11880
      %11880 = OpLabel
      %22245 = OpAccessChain %_ptr_Input_uint %gl_WorkGroupID %uint_0
      %15627 = OpLoad %uint %22245
      %22225 = OpAccessChain %_ptr_PushConstant_uint %push_consts_xe %int_3
       %7085 = OpLoad %uint %22225
       %7405 = OpUGreaterThanEqual %bool %15627 %7085
               OpSelectionMerge %16413 None
               OpBranchConditional %7405 %21992 %16413
      %21992 = OpLabel
               OpBranch %14903
      %16413 = OpLabel
      %20632 = OpAccessChain %_ptr_PushConstant_uint %push_consts_xe %int_2
      %15628 = OpLoad %uint %20632
      %20154 = OpAccessChain %_ptr_PushConstant_uint %push_consts_xe %int_0
      %22408 = OpLoad %uint %20154
      %21427 = OpAccessChain %_ptr_PushConstant_uint %push_consts_xe %int_1
      %13382 = OpLoad %uint %21427
      %14814 = OpIMul %uint %22408 %13382
      %14295 = OpShiftLeftLogical %uint %uint_1024 %15628
       %8408 = OpIMul %uint %14295 %14814
      %16854 = OpShiftRightLogical %uint %14295 %uint_2
      %17187 = OpAccessChain %_ptr_PushConstant_uint %push_consts_xe %int_5
       %7203 = OpLoad %uint %17187
      %24311 = OpINotEqual %bool %7203 %uint_0
      %23629 = OpUGreaterThan %bool %14814 %uint_1
      %11037 = OpLogicalAnd %bool %24311 %23629
               OpSelectionMerge %15645 None
               OpBranchConditional %11037 %11410 %15645
      %11410 = OpLabel
      %22390 = OpShiftRightLogical %uint %22408 %uint_1
       %6818 = OpShiftRightLogical %uint %13382 %uint_1
               OpBranch %15645
      %15645 = OpLabel
       %7755 = OpPhi %uint %uint_0 %16413 %6818 %11410
      %10303 = OpPhi %uint %uint_0 %16413 %22390 %11410
       %6812 = OpAccessChain %_ptr_PushConstant_uint %push_consts_xe %int_4
      %25189 = OpLoad %uint %6812
       %7507 = OpIMul %uint %15627 %8408
      %15833 = OpIAdd %uint %25189 %7507
      %15203 = OpIMul %uint %15627 %14295
       %7082 = OpLoad %uint %gl_LocalInvocationIndex
               OpBranch %13310
      %13310 = OpLabel
      %23131 = OpPhi %uint %7082 %15645 %22029 %9086
      %13910 = OpULessThan %bool %23131 %16854
               OpLoopMerge %6980 %9086 None
               OpBranchConditional %13910 %12232 %6980
      %12232 = OpLabel
      %15997 = OpShiftLeftLogical %uint %23131 %uint_2
       %6955 = OpIAdd %uint %15203 %15997
       %7704 = OpUGreaterThanEqual %bool %15628 %uint_2
               OpSelectionMerge %18021 None
               OpBranchConditional %7704 %16569 %7477
      %16569 = OpLabel
      %19162 = OpIEqual %bool %15628 %uint_3
               OpSelectionMerge %6567 None
               OpBranchConditional %19162 %11590 %15814
      %11590 = OpLabel
      %10033 = OpBitwiseAnd %uint %15997 %uint_4
               OpBranch %6567
      %15814 = OpLabel
               OpBranch %6567
       %6567 = OpLabel
      %21322 = OpPhi %uint %10033 %11590 %uint_0 %15814
       %9781 = OpULessThanEqual %bool %15628 %uint_2
      %21939 = OpSelect %uint %9781 %uint_7 %uint_6
       %9314 = OpShiftRightLogical %uint %15997 %21939
      %20330 = OpShiftLeftLogical %uint %uint_1 %21939
      %18570 = OpISub %uint %20330 %uint_1
      %19811 = OpBitwiseAnd %uint %15997 %18570
      %14152 = OpShiftRightLogical %uint %19811 %15628
       %9119 = OpIEqual %bool %15628 %uint_0
               OpSelectionMerge %21264 None
               OpBranchConditional %9119 %10545 %8778
      %10545 = OpLabel
      %18617 = OpBitwiseAnd %uint %14152 %uint_7
       %6778 = OpShiftRightLogical %uint %14152 %uint_6
       %8190 = OpBitwiseAnd %uint %6778 %uint_1
      %24033 = OpShiftLeftLogical %uint %8190 %uint_3
      %18005 = OpBitwiseOr %uint %18617 %24033
      %23113 = OpShiftRightLogical %uint %14152 %uint_4
       %6961 = OpBitwiseAnd %uint %23113 %uint_1
      %21040 = OpShiftRightLogical %uint %14152 %uint_3
       %8191 = OpBitwiseAnd %uint %21040 %uint_1
      %24034 = OpShiftLeftLogical %uint %8191 %uint_1
      %18006 = OpBitwiseOr %uint %6961 %24034
      %23151 = OpShiftRightLogical %uint %14152 %uint_5
       %6577 = OpBitwiseAnd %uint %23151 %uint_1
      %25078 = OpShiftLeftLogical %uint %6577 %uint_2
       %9421 = OpBitwiseOr %uint %18006 %25078
               OpBranch %21264
       %8778 = OpLabel
      %21584 = OpIEqual %bool %15628 %uint_1
               OpSelectionMerge %21263 None
               OpBranchConditional %21584 %10546 %10391
      %10546 = OpLabel
      %18618 = OpBitwiseAnd %uint %14152 %uint_7
       %6779 = OpShiftRightLogical %uint %14152 %uint_5
       %8192 = OpBitwiseAnd %uint %6779 %uint_1
      %24035 = OpShiftLeftLogical %uint %8192 %uint_3
      %18007 = OpBitwiseOr %uint %18618 %24035
      %24158 = OpShiftRightLogical %uint %14152 %uint_3
      %17448 = OpBitwiseAnd %uint %24158 %uint_3
               OpBranch %21263
      %10391 = OpLabel
      %21585 = OpIEqual %bool %15628 %uint_2
               OpSelectionMerge %16449 None
               OpBranchConditional %21585 %10547 %23438
      %10547 = OpLabel
      %18619 = OpBitwiseAnd %uint %14152 %uint_3
       %6780 = OpShiftRightLogical %uint %14152 %uint_3
       %8193 = OpBitwiseAnd %uint %6780 %uint_3
      %24036 = OpShiftLeftLogical %uint %8193 %uint_2
      %18008 = OpBitwiseOr %uint %18619 %24036
      %24159 = OpShiftRightLogical %uint %14152 %uint_2
      %17449 = OpBitwiseAnd %uint %24159 %uint_1
               OpBranch %16449
      %23438 = OpLabel
      %21039 = OpBitwiseAnd %uint %14152 %uint_1
       %6781 = OpShiftRightLogical %uint %14152 %uint_2
       %8194 = OpBitwiseAnd %uint %6781 %uint_1
      %24037 = OpShiftLeftLogical %uint %8194 %uint_1
      %18009 = OpBitwiseOr %uint %21039 %24037
      %24160 = OpShiftRightLogical %uint %14152 %uint_1
      %17450 = OpBitwiseAnd %uint %24160 %uint_1
               OpBranch %16449
      %16449 = OpLabel
      %11251 = OpPhi %uint %17449 %10547 %17450 %23438
      %13709 = OpPhi %uint %18008 %10547 %18009 %23438
               OpBranch %21263
      %21263 = OpLabel
      %11252 = OpPhi %uint %17448 %10546 %11251 %16449
      %13710 = OpPhi %uint %18007 %10546 %13709 %16449
               OpBranch %21264
      %21264 = OpLabel
       %9826 = OpPhi %uint %9421 %10545 %11252 %21263
      %14051 = OpPhi %uint %18005 %10545 %13710 %21263
      %11861 = OpUGreaterThanEqual %bool %15628 %uint_3
               OpSelectionMerge %22522 None
               OpBranchConditional %11861 %23527 %8593
      %23527 = OpLabel
       %9677 = OpISub %uint %uint_5 %15628
               OpBranch %22522
       %8593 = OpLabel
               OpBranch %22522
      %22522 = OpLabel
      %10811 = OpPhi %uint %9677 %23527 %uint_4 %8593
      %17875 = OpExtInst %uint %1 UMin %15628 %uint_2
      %13916 = OpISub %uint %uint_3 %17875
      %21350 = OpIMul %uint %14051 %22408
      %11713 = OpIAdd %uint %21350 %10303
      %21638 = OpIMul %uint %9826 %13382
      %19699 = OpIAdd %uint %21638 %7755
      %15993 = OpShiftRightLogical %uint %11713 %10811
      %11940 = OpShiftRightLogical %uint %19699 %13916
      %15003 = OpIMul %uint %15993 %13382
       %7096 = OpIAdd %uint %15003 %11940
      %11952 = OpShiftLeftLogical %uint %uint_1 %10811
      %10578 = OpISub %uint %11952 %uint_1
      %18705 = OpBitwiseAnd %uint %11713 %10578
      %22845 = OpShiftLeftLogical %uint %uint_1 %13916
      %18120 = OpISub %uint %22845 %uint_1
      %11360 = OpBitwiseAnd %uint %19699 %18120
      %14585 = OpIAdd %uint %10811 %15628
      %16607 = OpIAdd %uint %14585 %13916
      %16341 = OpShiftLeftLogical %uint %7096 %16607
      %16788 = OpShiftLeftLogical %uint %11360 %14585
      %18430 = OpBitwiseOr %uint %16341 %16788
      %24966 = OpShiftLeftLogical %uint %18705 %15628
       %6774 = OpBitwiseOr %uint %18430 %24966
       %7428 = OpIMul %uint %20330 %14814
      %23383 = OpIMul %uint %9314 %7428
       %7561 = OpIAdd %uint %15833 %23383
      %16268 = OpIAdd %uint %7561 %6774
       %8081 = OpIAdd %uint %16268 %21322
      %11494 = OpShiftRightLogical %uint %6955 %int_2
      %22258 = OpShiftRightLogical %uint %8081 %int_2
       %7363 = OpAccessChain %_ptr_Uniform_uint %xe_downscale_source %int_0 %22258
      %23451 = OpLoad %uint %7363
      %23477 = OpAccessChain %_ptr_Uniform_uint %xe_downscale_dest %int_0 %11494
               OpStore %23477 %23451
               OpBranch %18021
       %7477 = OpLabel
      %23459 = OpShiftRightLogical %uint %uint_4 %15628
      %17684 = OpShiftLeftLogical %uint %uint_1 %15628
      %23737 = OpShiftLeftLogical %uint %uint_8 %15628
      %19958 = OpShiftLeftLogical %uint %uint_1 %23737
      %12559 = OpISub %uint %19958 %uint_1
               OpBranch %9228
       %9228 = OpLabel
       %9864 = OpPhi %uint %uint_0 %7477 %22884 %16082
      %13686 = OpPhi %uint %uint_0 %7477 %22028 %16082
      %14719 = OpULessThan %bool %13686 %23459
               OpLoopMerge %13018 %16082 None
               OpBranchConditional %14719 %23304 %13018
      %23304 = OpLabel
      %12894 = OpIMul %uint %13686 %17684
      %15760 = OpIAdd %uint %15997 %12894
      %19087 = OpULessThanEqual %bool %15628 %uint_2
      %20905 = OpSelect %uint %19087 %uint_7 %uint_6
       %9315 = OpShiftRightLogical %uint %15760 %20905
      %20331 = OpShiftLeftLogical %uint %uint_1 %20905
      %18571 = OpISub %uint %20331 %uint_1
      %19812 = OpBitwiseAnd %uint %15760 %18571
      %14153 = OpShiftRightLogical %uint %19812 %15628
       %9120 = OpIEqual %bool %15628 %uint_0
               OpSelectionMerge %21266 None
               OpBranchConditional %9120 %10548 %8779
      %10548 = OpLabel
      %18620 = OpBitwiseAnd %uint %14153 %uint_7
       %6782 = OpShiftRightLogical %uint %14153 %uint_6
       %8195 = OpBitwiseAnd %uint %6782 %uint_1
      %24038 = OpShiftLeftLogical %uint %8195 %uint_3
      %18010 = OpBitwiseOr %uint %18620 %24038
      %23114 = OpShiftRightLogical %uint %14153 %uint_4
       %6962 = OpBitwiseAnd %uint %23114 %uint_1
      %21041 = OpShiftRightLogical %uint %14153 %uint_3
       %8196 = OpBitwiseAnd %uint %21041 %uint_1
      %24039 = OpShiftLeftLogical %uint %8196 %uint_1
      %18011 = OpBitwiseOr %uint %6962 %24039
      %23152 = OpShiftRightLogical %uint %14153 %uint_5
       %6578 = OpBitwiseAnd %uint %23152 %uint_1
      %25079 = OpShiftLeftLogical %uint %6578 %uint_2
       %9422 = OpBitwiseOr %uint %18011 %25079
               OpBranch %21266
       %8779 = OpLabel
      %21586 = OpIEqual %bool %15628 %uint_1
               OpSelectionMerge %21265 None
               OpBranchConditional %21586 %10549 %10392
      %10549 = OpLabel
      %18621 = OpBitwiseAnd %uint %14153 %uint_7
       %6783 = OpShiftRightLogical %uint %14153 %uint_5
       %8197 = OpBitwiseAnd %uint %6783 %uint_1
      %24040 = OpShiftLeftLogical %uint %8197 %uint_3
      %18012 = OpBitwiseOr %uint %18621 %24040
      %24161 = OpShiftRightLogical %uint %14153 %uint_3
      %17451 = OpBitwiseAnd %uint %24161 %uint_3
               OpBranch %21265
      %10392 = OpLabel
      %21587 = OpIEqual %bool %15628 %uint_2
               OpSelectionMerge %16450 None
               OpBranchConditional %21587 %10550 %23439
      %10550 = OpLabel
      %18622 = OpBitwiseAnd %uint %14153 %uint_3
       %6784 = OpShiftRightLogical %uint %14153 %uint_3
       %8198 = OpBitwiseAnd %uint %6784 %uint_3
      %24041 = OpShiftLeftLogical %uint %8198 %uint_2
      %18013 = OpBitwiseOr %uint %18622 %24041
      %24162 = OpShiftRightLogical %uint %14153 %uint_2
      %17452 = OpBitwiseAnd %uint %24162 %uint_1
               OpBranch %16450
      %23439 = OpLabel
      %21042 = OpBitwiseAnd %uint %14153 %uint_1
       %6785 = OpShiftRightLogical %uint %14153 %uint_2
       %8199 = OpBitwiseAnd %uint %6785 %uint_1
      %24042 = OpShiftLeftLogical %uint %8199 %uint_1
      %18014 = OpBitwiseOr %uint %21042 %24042
      %24163 = OpShiftRightLogical %uint %14153 %uint_1
      %17453 = OpBitwiseAnd %uint %24163 %uint_1
               OpBranch %16450
      %16450 = OpLabel
      %11253 = OpPhi %uint %17452 %10550 %17453 %23439
      %13711 = OpPhi %uint %18013 %10550 %18014 %23439
               OpBranch %21265
      %21265 = OpLabel
      %11254 = OpPhi %uint %17451 %10549 %11253 %16450
      %13712 = OpPhi %uint %18012 %10549 %13711 %16450
               OpBranch %21266
      %21266 = OpLabel
       %9827 = OpPhi %uint %9422 %10548 %11254 %21265
      %14052 = OpPhi %uint %18010 %10548 %13712 %21265
      %11862 = OpUGreaterThanEqual %bool %15628 %uint_3
               OpSelectionMerge %22523 None
               OpBranchConditional %11862 %23528 %8594
      %23528 = OpLabel
       %9678 = OpISub %uint %uint_5 %15628
               OpBranch %22523
       %8594 = OpLabel
               OpBranch %22523
      %22523 = OpLabel
      %10812 = OpPhi %uint %9678 %23528 %uint_4 %8594
      %17876 = OpExtInst %uint %1 UMin %15628 %uint_2
      %13917 = OpISub %uint %uint_3 %17876
      %21351 = OpIMul %uint %14052 %22408
      %11714 = OpIAdd %uint %21351 %10303
      %21639 = OpIMul %uint %9827 %13382
      %19700 = OpIAdd %uint %21639 %7755
      %15994 = OpShiftRightLogical %uint %11714 %10812
      %11941 = OpShiftRightLogical %uint %19700 %13917
      %15004 = OpIMul %uint %15994 %13382
       %7097 = OpIAdd %uint %15004 %11941
      %11953 = OpShiftLeftLogical %uint %uint_1 %10812
      %10579 = OpISub %uint %11953 %uint_1
      %18706 = OpBitwiseAnd %uint %11714 %10579
      %22846 = OpShiftLeftLogical %uint %uint_1 %13917
      %18121 = OpISub %uint %22846 %uint_1
      %11361 = OpBitwiseAnd %uint %19700 %18121
      %14586 = OpIAdd %uint %10812 %15628
      %16608 = OpIAdd %uint %14586 %13917
      %16342 = OpShiftLeftLogical %uint %7097 %16608
      %16789 = OpShiftLeftLogical %uint %11361 %14586
      %18431 = OpBitwiseOr %uint %16342 %16789
      %24967 = OpShiftLeftLogical %uint %18706 %15628
       %6775 = OpBitwiseOr %uint %18431 %24967
       %7429 = OpIMul %uint %20331 %14814
      %23384 = OpIMul %uint %9315 %7429
       %8910 = OpIAdd %uint %15833 %23384
      %23056 = OpIAdd %uint %8910 %6775
       %8671 = OpBitwiseAnd %uint %23056 %uint_4294967292
       %8099 = OpShiftRightLogical %uint %8671 %int_2
      %10713 = OpAccessChain %_ptr_Uniform_uint %xe_downscale_source %int_0 %8099
      %21886 = OpLoad %uint %10713
      %20120 = OpBitwiseAnd %uint %23056 %uint_3
      %23623 = OpShiftLeftLogical %uint %20120 %uint_3
      %21375 = OpShiftRightLogical %uint %21886 %23623
      %13595 = OpBitwiseAnd %uint %21375 %12559
      %14627 = OpIMul %uint %13686 %23737
      %18537 = OpShiftLeftLogical %uint %13595 %14627
      %22884 = OpBitwiseOr %uint %9864 %18537
               OpBranch %16082
      %16082 = OpLabel
      %22028 = OpIAdd %uint %13686 %int_1
               OpBranch %9228
      %13018 = OpLabel
      %24505 = OpShiftRightLogical %uint %6955 %int_2
      %15495 = OpAccessChain %_ptr_Uniform_uint %xe_downscale_dest %int_0 %24505
               OpStore %15495 %9864
               OpBranch %18021
      %18021 = OpLabel
               OpBranch %9086
       %9086 = OpLabel
      %22029 = OpIAdd %uint %23131 %uint_128
               OpBranch %13310
       %6980 = OpLabel
               OpBranch %14903
      %14903 = OpLabel
               OpReturn
               OpFunctionEnd
#endif

const uint32_t resolve_downscale_cs[] = {
    0x07230203, 0x00010000, 0x0008000B, 0x00006266, 0x00000000, 0x00020011,
    0x00000001, 0x0006000B, 0x00000001, 0x4C534C47, 0x6474732E, 0x3035342E,
    0x00000000, 0x0003000E, 0x00000000, 0x00000001, 0x0007000F, 0x00000005,
    0x0000161F, 0x6E69616D, 0x00000000, 0x00000BEF, 0x00000C15, 0x00060010,
    0x0000161F, 0x00000011, 0x00000080, 0x00000001, 0x00000001, 0x00030003,
    0x00000002, 0x000001CC, 0x00090004, 0x455F4C47, 0x635F5458, 0x72746E6F,
    0x665F6C6F, 0x5F776F6C, 0x72747461, 0x74756269, 0x00007365, 0x000B0004,
    0x455F4C47, 0x735F5458, 0x6C706D61, 0x656C7265, 0x745F7373, 0x75747865,
    0x665F6572, 0x74636E75, 0x736E6F69, 0x00000000, 0x000A0004, 0x475F4C47,
    0x4C474F4F, 0x70635F45, 0x74735F70, 0x5F656C79, 0x656E696C, 0x7269645F,
    0x69746365, 0x00006576, 0x00080004, 0x475F4C47, 0x4C474F4F, 0x6E695F45,
    0x64756C63, 0x69645F65, 0x74636572, 0x00657669, 0x00040005, 0x0000161F,
    0x6E69616D, 0x00000000, 0x00060005, 0x00000BEF, 0x575F6C67, 0x476B726F,
    0x70756F72, 0x00004449, 0x00070005, 0x00000420, 0x68737570, 0x6E6F635F,
    0x625F7473, 0x6B636F6C, 0x0065785F, 0x00090006, 0x00000420, 0x00000000,
    0x645F6578, 0x736E776F, 0x656C6163, 0x6163735F, 0x785F656C, 0x00000000,
    0x00090006, 0x00000420, 0x00000001, 0x645F6578, 0x736E776F, 0x656C6163,
    0x6163735F, 0x795F656C, 0x00000000, 0x000B0006, 0x00000420, 0x00000002,
    0x645F6578, 0x736E776F, 0x656C6163, 0x7869705F, 0x735F6C65, 0x5F657A69,
    0x32676F6C, 0x00000000, 0x00090006, 0x00000420, 0x00000003, 0x645F6578,
    0x736E776F, 0x656C6163, 0x6C69745F, 0x6F635F65, 0x00746E75, 0x000C0006,
    0x00000420, 0x00000004, 0x645F6578, 0x736E776F, 0x656C6163, 0x756F735F,
    0x5F656372, 0x7366666F, 0x625F7465, 0x73657479, 0x00000000, 0x000B0006,
    0x00000420, 0x00000005, 0x645F6578, 0x736E776F, 0x656C6163, 0x6C61685F,
    0x69705F66, 0x5F6C6578, 0x7366666F, 0x00007465, 0x00060005, 0x00000CE9,
    0x68737570, 0x6E6F635F, 0x5F737473, 0x00006578, 0x00080005, 0x00000C15,
    0x4C5F6C67, 0x6C61636F, 0x6F766E49, 0x69746163, 0x6E496E6F, 0x00786564,
    0x00090005, 0x0000079C, 0x645F6578, 0x736E776F, 0x656C6163, 0x7365645F,
    0x65785F74, 0x6F6C625F, 0x00006B63, 0x00050006, 0x0000079C, 0x00000000,
    0x61746164, 0x00000000, 0x00070005, 0x000012A2, 0x645F6578, 0x736E776F,
    0x656C6163, 0x7365645F, 0x00000074, 0x000A0005, 0x0000079D, 0x645F6578,
    0x736E776F, 0x656C6163, 0x756F735F, 0x5F656372, 0x625F6578, 0x6B636F6C,
    0x00000000, 0x00050006, 0x0000079D, 0x00000000, 0x61746164, 0x00000000,
    0x00070005, 0x00001622, 0x645F6578, 0x736E776F, 0x656C6163, 0x756F735F,
    0x00656372, 0x00040047, 0x00000BEF, 0x0000000B, 0x0000001A, 0x00030047,
    0x00000420, 0x00000002, 0x00050048, 0x00000420, 0x00000000, 0x00000023,
    0x00000000, 0x00050048, 0x00000420, 0x00000001, 0x00000023, 0x00000004,
    0x00050048, 0x00000420, 0x00000002, 0x00000023, 0x00000008, 0x00050048,
    0x00000420, 0x00000003, 0x00000023, 0x0000000C, 0x00050048, 0x00000420,
    0x00000004, 0x00000023, 0x00000010, 0x00050048, 0x00000420, 0x00000005,
    0x00000023, 0x00000014, 0x00040047, 0x00000C15, 0x0000000B, 0x0000001D,
    0x00040047, 0x000007D0, 0x00000006, 0x00000004, 0x00030047, 0x0000079C,
    0x00000003, 0x00040048, 0x0000079C, 0x00000000, 0x00000019, 0x00050048,
    0x0000079C, 0x00000000, 0x00000023, 0x00000000, 0x00030047, 0x000012A2,
    0x00000019, 0x00040047, 0x000012A2, 0x00000021, 0x00000000, 0x00040047,
    0x000012A2, 0x00000022, 0x00000001, 0x00040047, 0x000007D1, 0x00000006,
    0x00000004, 0x00030047, 0x0000079D, 0x00000003, 0x00040048, 0x0000079D,
    0x00000000, 0x00000018, 0x00050048, 0x0000079D, 0x00000000, 0x00000023,
    0x00000000, 0x00030047, 0x00001622, 0x00000018, 0x00040047, 0x00001622,
    0x00000021, 0x00000000, 0x00040047, 0x00001622, 0x00000022, 0x00000000,
    0x00040047, 0x000002E8, 0x0000000B, 0x00000019, 0x00020013, 0x00000008,
    0x00030021, 0x00000502, 0x00000008, 0x00040015, 0x0000000B, 0x00000020,
    0x00000000, 0x0004002B, 0x0000000B, 0x00000A10, 0x00000002, 0x00020014,
    0x00000009, 0x0004002B, 0x0000000B, 0x00000A1F, 0x00000007, 0x0004002B,
    0x0000000B, 0x00000A1C, 0x00000006, 0x0004002B, 0x0000000B, 0x00000A0D,
    0x00000001, 0x0004002B, 0x0000000B, 0x00000A0A, 0x00000000, 0x0004002B,
    0x0000000B, 0x00000A13, 0x00000003, 0x0004002B, 0x0000000B, 0x00000A16,
    0x00000004, 0x0004002B, 0x0000000B, 0x00000A19, 0x00000005, 0x00040017,
    0x00000014, 0x0000000B, 0x00000003, 0x00040020, 0x00000291, 0x00000001,
    0x00000014, 0x0004003B, 0x00000291, 0x00000BEF, 0x00000001, 0x00040020,
    0x00000288, 0x00000001, 0x0000000B, 0x0008001E, 0x00000420, 0x0000000B,
    0x0000000B, 0x0000000B, 0x0000000B, 0x0000000B, 0x0000000B, 0x00040020,
    0x0000069D, 0x00000009, 0x00000420, 0x0004003B, 0x0000069D, 0x00000CE9,
    0x00000009, 0x00040015, 0x0000000C, 0x00000020, 0x00000001, 0x0004002B,
    0x0000000C, 0x00000A14, 0x00000003, 0x00040020, 0x00000289, 0x00000009,
    0x0000000B, 0x0004002B, 0x0000000C, 0x00000A11, 0x00000002, 0x0004002B,
    0x0000000C, 0x00000A0B, 0x00000000, 0x0004002B, 0x0000000C, 0x00000A0E,
    0x00000001, 0x0004002B, 0x0000000B, 0x00000A47, 0x00000400, 0x0004002B,
    0x0000000C, 0x00000A1A, 0x00000005, 0x0004002B, 0x0000000C, 0x00000A17,
    0x00000004, 0x0004003B, 0x00000288, 0x00000C15, 0x00000001, 0x0003001D,
    0x000007D0, 0x0000000B, 0x0003001E, 0x0000079C, 0x000007D0, 0x00040020,
    0x00000A1B, 0x00000002, 0x0000079C, 0x0004003B, 0x00000A1B, 0x000012A2,
    0x00000002, 0x0003001D, 0x000007D1, 0x0000000B, 0x0003001E, 0x0000079D,
    0x000007D1, 0x00040020, 0x00000A1D, 0x00000002, 0x0000079D, 0x0004003B,
    0x00000A1D, 0x00001622, 0x00000002, 0x00040020, 0x0000028A, 0x00000002,
    0x0000000B, 0x0004002B, 0x0000000B, 0x00000A22, 0x00000008, 0x0004002B,
    0x0000000B, 0x000009FE, 0xFFFFFFFC, 0x0004002B, 0x0000000B, 0x00000B8A,
    0x00000080, 0x0006002C, 0x00000014, 0x000002E8, 0x00000B8A, 0x00000A0D,
    0x00000A0D, 0x00050036, 0x00000008, 0x0000161F, 0x00000000, 0x00000502,
    0x000200F8, 0x00003B06, 0x000300F7, 0x00003A37, 0x00000000, 0x000300FB,
    0x00000A0A, 0x00002E68, 0x000200F8, 0x00002E68, 0x00050041, 0x00000288,
    0x000056E5, 0x00000BEF, 0x00000A0A, 0x0004003D, 0x0000000B, 0x00003D0B,
    0x000056E5, 0x00050041, 0x00000289, 0x000056D1, 0x00000CE9, 0x00000A14,
    0x0004003D, 0x0000000B, 0x00001BAD, 0x000056D1, 0x000500AE, 0x00000009,
    0x00001CED, 0x00003D0B, 0x00001BAD, 0x000300F7, 0x0000401D, 0x00000000,
    0x000400FA, 0x00001CED, 0x000055E8, 0x0000401D, 0x000200F8, 0x000055E8,
    0x000200F9, 0x00003A37, 0x000200F8, 0x0000401D, 0x00050041, 0x00000289,
    0x00005098, 0x00000CE9, 0x00000A11, 0x0004003D, 0x0000000B, 0x00003D0C,
    0x00005098, 0x00050041, 0x00000289, 0x00004EBA, 0x00000CE9, 0x00000A0B,
    0x0004003D, 0x0000000B, 0x00005788, 0x00004EBA, 0x00050041, 0x00000289,
    0x000053B3, 0x00000CE9, 0x00000A0E, 0x0004003D, 0x0000000B, 0x00003446,
    0x000053B3, 0x00050084, 0x0000000B, 0x000039DE, 0x00005788, 0x00003446,
    0x000500C4, 0x0000000B, 0x000037D7, 0x00000A47, 0x00003D0C, 0x00050084,
    0x0000000B, 0x000020D8, 0x000037D7, 0x000039DE, 0x000500C2, 0x0000000B,
    0x000041D6, 0x000037D7, 0x00000A10, 0x00050041, 0x00000289, 0x00004323,
    0x00000CE9, 0x00000A1A, 0x0004003D, 0x0000000B, 0x00001C23, 0x00004323,
    0x000500AB, 0x00000009, 0x00005EF7, 0x00001C23, 0x00000A0A, 0x000500AC,
    0x00000009, 0x00005C4D, 0x000039DE, 0x00000A0D, 0x000500A7, 0x00000009,
    0x00002B1D, 0x00005EF7, 0x00005C4D, 0x000300F7, 0x00003D1D, 0x00000000,
    0x000400FA, 0x00002B1D, 0x00002C92, 0x00003D1D, 0x000200F8, 0x00002C92,
    0x000500C2, 0x0000000B, 0x00005776, 0x00005788, 0x00000A0D, 0x000500C2,
    0x0000000B, 0x00001AA2, 0x00003446, 0x00000A0D, 0x000200F9, 0x00003D1D,
    0x000200F8, 0x00003D1D, 0x000700F5, 0x0000000B, 0x00001E4B, 0x00000A0A,
    0x0000401D, 0x00001AA2, 0x00002C92, 0x000700F5, 0x0000000B, 0x0000283F,
    0x00000A0A, 0x0000401D, 0x00005776, 0x00002C92, 0x00050041, 0x00000289,
    0x00001A9C, 0x00000CE9, 0x00000A17, 0x0004003D, 0x0000000B, 0x00006265,
    0x00001A9C, 0x00050084, 0x0000000B, 0x00001D53, 0x00003D0B, 0x000020D8,
    0x00050080, 0x0000000B, 0x00003DD9, 0x00006265, 0x00001D53, 0x00050084,
    0x0000000B, 0x00003B63, 0x00003D0B, 0x000037D7, 0x0004003D, 0x0000000B,
    0x00001BAA, 0x00000C15, 0x000200F9, 0x000033FE, 0x000200F8, 0x000033FE,
    0x000700F5, 0x0000000B, 0x00005A5B, 0x00001BAA, 0x00003D1D, 0x0000560D,
    0x0000237E, 0x000500B0, 0x00000009, 0x00003656, 0x00005A5B, 0x000041D6,
    0x000400F6, 0x00001B44, 0x0000237E, 0x00000000, 0x000400FA, 0x00003656,
    0x00002FC8, 0x00001B44, 0x000200F8, 0x00002FC8, 0x000500C4, 0x0000000B,
    0x00003E7D, 0x00005A5B, 0x00000A10, 0x00050080, 0x0000000B, 0x00001B2B,
    0x00003B63, 0x00003E7D, 0x000500AE, 0x00000009, 0x00001E18, 0x00003D0C,
    0x00000A10, 0x000300F7, 0x00004665, 0x00000000, 0x000400FA, 0x00001E18,
    0x000040B9, 0x00001D35, 0x000200F8, 0x000040B9, 0x000500AA, 0x00000009,
    0x00004ADA, 0x00003D0C, 0x00000A13, 0x000300F7, 0x000019A7, 0x00000000,
    0x000400FA, 0x00004ADA, 0x00002D46, 0x00003DC6, 0x000200F8, 0x00002D46,
    0x000500C7, 0x0000000B, 0x00002731, 0x00003E7D, 0x00000A16, 0x000200F9,
    0x000019A7, 0x000200F8, 0x00003DC6, 0x000200F9, 0x000019A7, 0x000200F8,
    0x000019A7, 0x000700F5, 0x0000000B, 0x0000534A, 0x00002731, 0x00002D46,
    0x00000A0A, 0x00003DC6, 0x000500B2, 0x00000009, 0x00002635, 0x00003D0C,
    0x00000A10, 0x000600A9, 0x0000000B, 0x000055B3, 0x00002635, 0x00000A1F,
    0x00000A1C, 0x000500C2, 0x0000000B, 0x00002462, 0x00003E7D, 0x000055B3,
    0x000500C4, 0x0000000B, 0x00004F6A, 0x00000A0D, 0x000055B3, 0x00050082,
    0x0000000B, 0x0000488A, 0x00004F6A, 0x00000A0D, 0x000500C7, 0x0000000B,
    0x00004D63, 0x00003E7D, 0x0000488A, 0x000500C2, 0x0000000B, 0x00003748,
    0x00004D63, 0x00003D0C, 0x000500AA, 0x00000009, 0x0000239F, 0x00003D0C,
    0x00000A0A, 0x000300F7, 0x00005310, 0x00000000, 0x000400FA, 0x0000239F,
    0x00002931, 0x0000224A, 0x000200F8, 0x00002931, 0x000500C7, 0x0000000B,
    0x000048B9, 0x00003748, 0x00000A1F, 0x000500C2, 0x0000000B, 0x00001A7A,
    0x00003748, 0x00000A1C, 0x000500C7, 0x0000000B, 0x00001FFE, 0x00001A7A,
    0x00000A0D, 0x000500C4, 0x0000000B, 0x00005DE1, 0x00001FFE, 0x00000A13,
    0x000500C5, 0x0000000B, 0x00004655, 0x000048B9, 0x00005DE1, 0x000500C2,
    0x0000000B, 0x00005A49, 0x00003748, 0x00000A16, 0x000500C7, 0x0000000B,
    0x00001B31, 0x00005A49, 0x00000A0D, 0x000500C2, 0x0000000B, 0x00005230,
    0x00003748, 0x00000A13, 0x000500C7, 0x0000000B, 0x00001FFF, 0x00005230,
    0x00000A0D, 0x000500C4, 0x0000000B, 0x00005DE2, 0x00001FFF, 0x00000A0D,
    0x000500C5, 0x0000000B, 0x00004656, 0x00001B31, 0x00005DE2, 0x000500C2,
    0x0000000B, 0x00005A6F, 0x00003748, 0x00000A19, 0x000500C7, 0x0000000B,
    0x000019B1, 0x00005A6F, 0x00000A0D, 0x000500C4, 0x0000000B, 0x000061F6,
    0x000019B1, 0x00000A10, 0x000500C5, 0x0000000B, 0x000024CD, 0x00004656,
    0x000061F6, 0x000200F9, 0x00005310, 0x000200F8, 0x0000224A, 0x000500AA,
    0x00000009, 0x00005450, 0x00003D0C, 0x00000A0D, 0x000300F7, 0x0000530F,
    0x00000000, 0x000400FA, 0x00005450, 0x00002932, 0x00002897, 0x000200F8,
    0x00002932, 0x000500C7, 0x0000000B, 0x000048BA, 0x00003748, 0x00000A1F,
    0x000500C2, 0x0000000B, 0x00001A7B, 0x00003748, 0x00000A19, 0x000500C7,
    0x0000000B, 0x00002000, 0x00001A7B, 0x00000A0D, 0x000500C4, 0x0000000B,
    0x00005DE3, 0x00002000, 0x00000A13, 0x000500C5, 0x0000000B, 0x00004657,
    0x000048BA, 0x00005DE3, 0x000500C2, 0x0000000B, 0x00005E5E, 0x00003748,
    0x00000A13, 0x000500C7, 0x0000000B, 0x00004428, 0x00005E5E, 0x00000A13,
    0x000200F9, 0x0000530F, 0x000200F8, 0x00002897, 0x000500AA, 0x00000009,
    0x00005451, 0x00003D0C, 0x00000A10, 0x000300F7, 0x00004041, 0x00000000,
    0x000400FA, 0x00005451, 0x00002933, 0x00005B8E, 0x000200F8, 0x00002933,
    0x000500C7, 0x0000000B, 0x000048BB, 0x00003748, 0x00000A13, 0x000500C2,
    0x0000000B, 0x00001A7C, 0x00003748, 0x00000A13, 0x000500C7, 0x0000000B,
    0x00002001, 0x00001A7C, 0x00000A13, 0x000500C4, 0x0000000B, 0x00005DE4,
    0x00002001, 0x00000A10, 0x000500C5, 0x0000000B, 0x00004658, 0x000048BB,
    0x00005DE4, 0x000500C2, 0x0000000B, 0x00005E5F, 0x00003748, 0x00000A10,
    0x000500C7, 0x0000000B, 0x00004429, 0x00005E5F, 0x00000A0D, 0x000200F9,
    0x00004041, 0x000200F8, 0x00005B8E, 0x000500C7, 0x0000000B, 0x0000522F,
    0x00003748, 0x00000A0D, 0x000500C2, 0x0000000B, 0x00001A7D, 0x00003748,
    0x00000A10, 0x000500C7, 0x0000000B, 0x00002002, 0x00001A7D, 0x00000A0D,
    0x000500C4, 0x0000000B, 0x00005DE5, 0x00002002, 0x00000A0D, 0x000500C5,
    0x0000000B, 0x00004659, 0x0000522F, 0x00005DE5, 0x000500C2, 0x0000000B,
    0x00005E60, 0x00003748, 0x00000A0D, 0x000500C7, 0x0000000B, 0x0000442A,
    0x00005E60, 0x00000A0D, 0x000200F9, 0x00004041, 0x000200F8, 0x00004041,
    0x000700F5, 0x0000000B, 0x00002BF3, 0x00004429, 0x00002933, 0x0000442A,
    0x00005B8E, 0x000700F5, 0x0000000B, 0x0000358D, 0x00004658, 0x00002933,
    0x00004659, 0x00005B8E, 0x000200F9, 0x0000530F, 0x000200F8, 0x0000530F,
    0x000700F5, 0x0000000B, 0x00002BF4, 0x00004428, 0x00002932, 0x00002BF3,
    0x00004041, 0x000700F5, 0x0000000B, 0x0000358E, 0x00004657, 0x00002932,
    0x0000358D, 0x00004041, 0x000200F9, 0x00005310, 0x000200F8, 0x00005310,
    0x000700F5, 0x0000000B, 0x00002662, 0x000024CD, 0x00002931, 0x00002BF4,
    0x0000530F, 0x000700F5, 0x0000000B, 0x000036E3, 0x00004655, 0x00002931,
    0x0000358E, 0x0000530F, 0x000500AE, 0x00000009, 0x00002E55, 0x00003D0C,
    0x00000A13, 0x000300F7, 0x000057FA, 0x00000000, 0x000400FA, 0x00002E55,
    0x00005BE7, 0x00002191, 0x000200F8, 0x00005BE7, 0x00050082, 0x0000000B,
    0x000025CD, 0x00000A19, 0x00003D0C, 0x000200F9, 0x000057FA, 0x000200F8,
    0x00002191, 0x000200F9, 0x000057FA, 0x000200F8, 0x000057FA, 0x000700F5,
    0x0000000B, 0x00002A3B, 0x000025CD, 0x00005BE7, 0x00000A16, 0x00002191,
    0x0007000C, 0x0000000B, 0x000045D3, 0x00000001, 0x00000026, 0x00003D0C,
    0x00000A10, 0x00050082, 0x0000000B, 0x0000365C, 0x00000A13, 0x000045D3,
    0x00050084, 0x0000000B, 0x00005366, 0x000036E3, 0x00005788, 0x00050080,
    0x0000000B, 0x00002DC1, 0x00005366, 0x0000283F, 0x00050084, 0x0000000B,
    0x00005486, 0x00002662, 0x00003446, 0x00050080, 0x0000000B, 0x00004CF3,
    0x00005486, 0x00001E4B, 0x000500C2, 0x0000000B, 0x00003E79, 0x00002DC1,
    0x00002A3B, 0x000500C2, 0x0000000B, 0x00002EA4, 0x00004CF3, 0x0000365C,
    0x00050084, 0x0000000B, 0x00003A9B, 0x00003E79, 0x00003446, 0x00050080,
    0x0000000B, 0x00001BB8, 0x00003A9B, 0x00002EA4, 0x000500C4, 0x0000000B,
    0x00002EB0, 0x00000A0D, 0x00002A3B, 0x00050082, 0x0000000B, 0x00002952,
    0x00002EB0, 0x00000A0D, 0x000500C7, 0x0000000B, 0x00004911, 0x00002DC1,
    0x00002952, 0x000500C4, 0x0000000B, 0x0000593D, 0x00000A0D, 0x0000365C,
    0x00050082, 0x0000000B, 0x000046C8, 0x0000593D, 0x00000A0D, 0x000500C7,
    0x0000000B, 0x00002C60, 0x00004CF3, 0x000046C8, 0x00050080, 0x0000000B,
    0x000038F9, 0x00002A3B, 0x00003D0C, 0x00050080, 0x0000000B, 0x000040DF,
    0x000038F9, 0x0000365C, 0x000500C4, 0x0000000B, 0x00003FD5, 0x00001BB8,
    0x000040DF, 0x000500C4, 0x0000000B, 0x00004194, 0x00002C60, 0x000038F9,
    0x000500C5, 0x0000000B, 0x000047FE, 0x00003FD5, 0x00004194, 0x000500C4,
    0x0000000B, 0x00006186, 0x00004911, 0x00003D0C, 0x000500C5, 0x0000000B,
    0x00001A76, 0x000047FE, 0x00006186, 0x00050084, 0x0000000B, 0x00001D04,
    0x00004F6A, 0x000039DE, 0x00050084, 0x0000000B, 0x00005B57, 0x00002462,
    0x00001D04, 0x00050080, 0x0000000B, 0x00001D89, 0x00003DD9, 0x00005B57,
    0x00050080, 0x0000000B, 0x00003F8C, 0x00001D89, 0x00001A76, 0x00050080,
    0x0000000B, 0x00001F91, 0x00003F8C, 0x0000534A, 0x000500C2, 0x0000000B,
    0x00002CE6, 0x00001B2B, 0x00000A11, 0x000500C2, 0x0000000B, 0x000056F2,
    0x00001F91, 0x00000A11, 0x00060041, 0x0000028A, 0x00001CC3, 0x00001622,
    0x00000A0B, 0x000056F2, 0x0004003D, 0x0000000B, 0x00005B9B, 0x00001CC3,
    0x00060041, 0x0000028A, 0x00005BB5, 0x000012A2, 0x00000A0B, 0x00002CE6,
    0x0003003E, 0x00005BB5, 0x00005B9B, 0x000200F9, 0x00004665, 0x000200F8,
    0x00001D35, 0x000500C2, 0x0000000B, 0x00005BA3, 0x00000A16, 0x00003D0C,
    0x000500C4, 0x0000000B, 0x00004514, 0x00000A0D, 0x00003D0C, 0x000500C4,
    0x0000000B, 0x00005CB9, 0x00000A22, 0x00003D0C, 0x000500C4, 0x0000000B,
    0x00004DF6, 0x00000A0D, 0x00005CB9, 0x00050082, 0x0000000B, 0x0000310F,
    0x00004DF6, 0x00000A0D, 0x000200F9, 0x0000240C, 0x000200F8, 0x0000240C,
    0x000700F5, 0x0000000B, 0x00002688, 0x00000A0A, 0x00001D35, 0x00005964,
    0x00003ED2, 0x000700F5, 0x0000000B, 0x00003576, 0x00000A0A, 0x00001D35,
    0x0000560C, 0x00003ED2, 0x000500B0, 0x00000009, 0x0000397F, 0x00003576,
    0x00005BA3, 0x000400F6, 0x000032DA, 0x00003ED2, 0x00000000, 0x000400FA,
    0x0000397F, 0x00005B08, 0x000032DA, 0x000200F8, 0x00005B08, 0x00050084,
    0x0000000B, 0x0000325E, 0x00003576, 0x00004514, 0x00050080, 0x0000000B,
    0x00003D90, 0x00003E7D, 0x0000325E, 0x000500B2, 0x00000009, 0x00004A8F,
    0x00003D0C, 0x00000A10, 0x000600A9, 0x0000000B, 0x000051A9, 0x00004A8F,
    0x00000A1F, 0x00000A1C, 0x000500C2, 0x0000000B, 0x00002463, 0x00003D90,
    0x000051A9, 0x000500C4, 0x0000000B, 0x00004F6B, 0x00000A0D, 0x000051A9,
    0x00050082, 0x0000000B, 0x0000488B, 0x00004F6B, 0x00000A0D, 0x000500C7,
    0x0000000B, 0x00004D64, 0x00003D90, 0x0000488B, 0x000500C2, 0x0000000B,
    0x00003749, 0x00004D64, 0x00003D0C, 0x000500AA, 0x00000009, 0x000023A0,
    0x00003D0C, 0x00000A0A, 0x000300F7, 0x00005312, 0x00000000, 0x000400FA,
    0x000023A0, 0x00002934, 0x0000224B, 0x000200F8, 0x00002934, 0x000500C7,
    0x0000000B, 0x000048BC, 0x00003749, 0x00000A1F, 0x000500C2, 0x0000000B,
    0x00001A7E, 0x00003749, 0x00000A1C, 0x000500C7, 0x0000000B, 0x00002003,
    0x00001A7E, 0x00000A0D, 0x000500C4, 0x0000000B, 0x00005DE6, 0x00002003,
    0x00000A13, 0x000500C5, 0x0000000B, 0x0000465A, 0x000048BC, 0x00005DE6,
    0x000500C2, 0x0000000B, 0x00005A4A, 0x00003749, 0x00000A16, 0x000500C7,
    0x0000000B, 0x00001B32, 0x00005A4A, 0x00000A0D, 0x000500C2, 0x0000000B,
    0x00005231, 0x00003749, 0x00000A13, 0x000500C7, 0x0000000B, 0x00002004,
    0x00005231, 0x00000A0D, 0x000500C4, 0x0000000B, 0x00005DE7, 0x00002004,
    0x00000A0D, 0x000500C5, 0x0000000B, 0x0000465B, 0x00001B32, 0x00005DE7,
    0x000500C2, 0x0000000B, 0x00005A70, 0x00003749, 0x00000A19, 0x000500C7,
    0x0000000B, 0x000019B2, 0x00005A70, 0x00000A0D, 0x000500C4, 0x0000000B,
    0x000061F7, 0x000019B2, 0x00000A10, 0x000500C5, 0x0000000B, 0x000024CE,
    0x0000465B, 0x000061F7, 0x000200F9, 0x00005312, 0x000200F8, 0x0000224B,
    0x000500AA, 0x00000009, 0x00005452, 0x00003D0C, 0x00000A0D, 0x000300F7,
    0x00005311, 0x00000000, 0x000400FA, 0x00005452, 0x00002935, 0x00002898,
    0x000200F8, 0x00002935, 0x000500C7, 0x0000000B, 0x000048BD, 0x00003749,
    0x00000A1F, 0x000500C2, 0x0000000B, 0x00001A7F, 0x00003749, 0x00000A19,
    0x000500C7, 0x0000000B, 0x00002005, 0x00001A7F, 0x00000A0D, 0x000500C4,
    0x0000000B, 0x00005DE8, 0x00002005, 0x00000A13, 0x000500C5, 0x0000000B,
    0x0000465C, 0x000048BD, 0x00005DE8, 0x000500C2, 0x0000000B, 0x00005E61,
    0x00003749, 0x00000A13, 0x000500C7, 0x0000000B, 0x0000442B, 0x00005E61,
    0x00000A13, 0x000200F9, 0x00005311, 0x000200F8, 0x00002898, 0x000500AA,
    0x00000009, 0x00005453, 0x00003D0C, 0x00000A10, 0x000300F7, 0x00004042,
    0x00000000, 0x000400FA, 0x00005453, 0x00002936, 0x00005B8F, 0x000200F8,
    0x00002936, 0x000500C7, 0x0000000B, 0x000048BE, 0x00003749, 0x00000A13,
    0x000500C2, 0x0000000B, 0x00001A80, 0x00003749, 0x00000A13, 0x000500C7,
    0x0000000B, 0x00002006, 0x00001A80, 0x00000A13, 0x000500C4, 0x0000000B,
    0x00005DE9, 0x00002006, 0x00000A10, 0x000500C5, 0x0000000B, 0x0000465D,
    0x000048BE, 0x00005DE9, 0x000500C2, 0x0000000B, 0x00005E62, 0x00003749,
    0x00000A10, 0x000500C7, 0x0000000B, 0x0000442C, 0x00005E62, 0x00000A0D,
    0x000200F9, 0x00004042, 0x000200F8, 0x00005B8F, 0x000500C7, 0x0000000B,
    0x00005232, 0x00003749, 0x00000A0D, 0x000500C2, 0x0000000B, 0x00001A81,
    0x00003749, 0x00000A10, 0x000500C7, 0x0000000B, 0x00002007, 0x00001A81,
    0x00000A0D, 0x000500C4, 0x0000000B, 0x00005DEA, 0x00002007, 0x00000A0D,
    0x000500C5, 0x0000000B, 0x0000465E, 0x00005232, 0x00005DEA, 0x000500C2,
    0x0000000B, 0x00005E63, 0x00003749, 0x00000A0D, 0x000500C7, 0x0000000B,
    0x0000442D, 0x00005E63, 0x00000A0D, 0x000200F9, 0x00004042, 0x000200F8,
    0x00004042, 0x000700F5, 0x0000000B, 0x00002BF5, 0x0000442C, 0x00002936,
    0x0000442D, 0x00005B8F, 0x000700F5, 0x0000000B, 0x0000358F, 0x0000465D,
    0x00002936, 0x0000465E, 0x00005B8F, 0x000200F9, 0x00005311, 0x000200F8,
    0x00005311, 0x000700F5, 0x0000000B, 0x00002BF6, 0x0000442B, 0x00002935,
    0x00002BF5, 0x00004042, 0x000700F5, 0x0000000B, 0x00003590, 0x0000465C,
    0x00002935, 0x0000358F, 0x00004042, 0x000200F9, 0x00005312, 0x000200F8,
    0x00005312, 0x000700F5, 0x0000000B, 0x00002663, 0x000024CE, 0x00002934,
    0x00002BF6, 0x00005311, 0x000700F5, 0x0000000B, 0x000036E4, 0x0000465A,
    0x00002934, 0x00003590, 0x00005311, 0x000500AE, 0x00000009, 0x00002E56,
    0x00003D0C, 0x00000A13, 0x000300F7, 0x000057FB, 0x00000000, 0x000400FA,
    0x00002E56, 0x00005BE8, 0x00002192, 0x000200F8, 0x00005BE8, 0x00050082,
    0x0000000B, 0x000025CE, 0x00000A19, 0x00003D0C, 0x000200F9, 0x000057FB,
    0x000200F8, 0x00002192, 0x000200F9, 0x000057FB, 0x000200F8, 0x000057FB,
    0x000700F5, 0x0000000B, 0x00002A3C, 0x000025CE, 0x00005BE8, 0x00000A16,
    0x00002192, 0x0007000C, 0x0000000B, 0x000045D4, 0x00000001, 0x00000026,
    0x00003D0C, 0x00000A10, 0x00050082, 0x0000000B, 0x0000365D, 0x00000A13,
    0x000045D4, 0x00050084, 0x0000000B, 0x00005367, 0x000036E4, 0x00005788,
    0x00050080, 0x0000000B, 0x00002DC2, 0x00005367, 0x0000283F, 0x00050084,
    0x0000000B, 0x00005487, 0x00002663, 0x00003446, 0x00050080, 0x0000000B,
    0x00004CF4, 0x00005487, 0x00001E4B, 0x000500C2, 0x0000000B, 0x00003E7A,
    0x00002DC2, 0x00002A3C, 0x000500C2, 0x0000000B, 0x00002EA5, 0x00004CF4,
    0x0000365D, 0x00050084, 0x0000000B, 0x00003A9C, 0x00003E7A, 0x00003446,
    0x00050080, 0x0000000B, 0x00001BB9, 0x00003A9C, 0x00002EA5, 0x000500C4,
    0x0000000B, 0x00002EB1, 0x00000A0D, 0x00002A3C, 0x00050082, 0x0000000B,
    0x00002953, 0x00002EB1, 0x00000A0D, 0x000500C7, 0x0000000B, 0x00004912,
    0x00002DC2, 0x00002953, 0x000500C4, 0x0000000B, 0x0000593E, 0x00000A0D,
    0x0000365D, 0x00050082, 0x0000000B, 0x000046C9, 0x0000593E, 0x00000A0D,
    0x000500C7, 0x0000000B, 0x00002C61, 0x00004CF4, 0x000046C9, 0x00050080,
    0x0000000B, 0x000038FA, 0x00002A3C, 0x00003D0C, 0x00050080, 0x0000000B,
    0x000040E0, 0x000038FA, 0x0000365D, 0x000500C4, 0x0000000B, 0x00003FD6,
    0x00001BB9, 0x000040E0, 0x000500C4, 0x0000000B, 0x00004195, 0x00002C61,
    0x000038FA, 0x000500C5, 0x0000000B, 0x000047FF, 0x00003FD6, 0x00004195,
    0x000500C4, 0x0000000B, 0x00006187, 0x00004912, 0x00003D0C, 0x000500C5,
    0x0000000B, 0x00001A77, 0x000047FF, 0x00006187, 0x00050084, 0x0000000B,
    0x00001D05, 0x00004F6B, 0x000039DE, 0x00050084, 0x0000000B, 0x00005B58,
    0x00002463, 0x00001D05, 0x00050080, 0x0000000B, 0x000022CE, 0x00003DD9,
    0x00005B58, 0x00050080, 0x0000000B, 0x00005A10, 0x000022CE, 0x00001A77,
    0x000500C7, 0x0000000B, 0x000021DF, 0x00005A10, 0x000009FE, 0x000500C2,
    0x0000000B, 0x00001FA3, 0x000021DF, 0x00000A11, 0x00060041, 0x0000028A,
    0x000029D9, 0x00001622, 0x00000A0B, 0x00001FA3, 0x0004003D, 0x0000000B,
    0x0000557E, 0x000029D9, 0x000500C7, 0x0000000B, 0x00004E98, 0x00005A10,
    0x00000A13, 0x000500C4, 0x0000000B, 0x00005C47, 0x00004E98, 0x00000A13,
    0x000500C2, 0x0000000B, 0x0000537F, 0x0000557E, 0x00005C47, 0x000500C7,
    0x0000000B, 0x0000351B, 0x0000537F, 0x0000310F, 0x00050084, 0x0000000B,
    0x00003923, 0x00003576, 0x00005CB9, 0x000500C4, 0x0000000B, 0x00004869,
    0x0000351B, 0x00003923, 0x000500C5, 0x0000000B, 0x00005964, 0x00002688,
    0x00004869, 0x000200F9, 0x00003ED2, 0x000200F8, 0x00003ED2, 0x00050080,
    0x0000000B, 0x0000560C, 0x00003576, 0x00000A0E, 0x000200F9, 0x0000240C,
    0x000200F8, 0x000032DA, 0x000500C2, 0x0000000B, 0x00005FB9, 0x00001B2B,
    0x00000A11, 0x00060041, 0x0000028A, 0x00003C87, 0x000012A2, 0x00000A0B,
    0x00005FB9, 0x0003003E, 0x00003C87, 0x00002688, 0x000200F9, 0x00004665,
    0x000200F8, 0x00004665, 0x000200F9, 0x0000237E, 0x000200F8, 0x0000237E,
    0x00050080, 0x0000000B, 0x0000560D, 0x00005A5B, 0x00000B8A, 0x000200F9,
    0x000033FE, 0x000200F8, 0x00001B44, 0x000200F9, 0x00003A37, 0x000200F8,
    0x00003A37, 0x000100FD, 0x00010038,
};

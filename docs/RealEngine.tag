<?xml version='1.0' encoding='UTF-8' standalone='yes' ?>
<tagfile doxygen_version="1.14.0" doxygen_gitid="cbe58f6237b2238c9af7f51c6b7afb8bbf52c866">
  <compound kind="class">
    <name>RealEngine::Application</name>
    <filename>class_real_engine_1_1_application.html</filename>
    <member kind="function">
      <type></type>
      <name>Application</name>
      <anchorfile>class_real_engine_1_1_application.html</anchorfile>
      <anchor>a294ac6087dfdc6e35b438bf57eec521a</anchor>
      <arglist>(const ApplicationSpecification &amp;specification)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Application</name>
      <anchorfile>class_real_engine_1_1_application.html</anchorfile>
      <anchor>a68a9bc1c987eab94635136a80da7083f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PushLayer</name>
      <anchorfile>class_real_engine_1_1_application.html</anchorfile>
      <anchor>ac043b21c75aa6701f580e666e098b77b</anchor>
      <arglist>(Layer *layer)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Run</name>
      <anchorfile>class_real_engine_1_1_application.html</anchorfile>
      <anchor>a5e7faa38c8c73ed92fb2f7d78171127c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Stop</name>
      <anchorfile>class_real_engine_1_1_application.html</anchorfile>
      <anchor>a9b3766627214b13f6467179366d74698</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>OnEvent</name>
      <anchorfile>class_real_engine_1_1_application.html</anchorfile>
      <anchor>a175a1c7d9650cb7f0ed767bd94147781</anchor>
      <arglist>(Event &amp;e)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>OnWindowClose</name>
      <anchorfile>class_real_engine_1_1_application.html</anchorfile>
      <anchor>a60a13e1dd3bc4b3a293e4b99be9bd0b4</anchor>
      <arglist>(WindowCloseEvent &amp;e)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>OnWindowResize</name>
      <anchorfile>class_real_engine_1_1_application.html</anchorfile>
      <anchor>aa8af476bfa3cc6a8c96990d52be4d0cb</anchor>
      <arglist>(WindowResizeEvent &amp;e)</arglist>
    </member>
    <member kind="function">
      <type>Window &amp;</type>
      <name>GetWindow</name>
      <anchorfile>class_real_engine_1_1_application.html</anchorfile>
      <anchor>accd3923de178068019f7a5f2bf7e24a0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Application &amp;</type>
      <name>Get</name>
      <anchorfile>class_real_engine_1_1_application.html</anchorfile>
      <anchor>a7b400b82b8c4d9dc4621e23f065ef47a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>const ApplicationSpecification</type>
      <name>m_Specification</name>
      <anchorfile>class_real_engine_1_1_application.html</anchorfile>
      <anchor>aab4b886d8b8122d29a6423eb6fc7b77f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>ImGuiLayer *</type>
      <name>m_ImGuiLayer</name>
      <anchorfile>class_real_engine_1_1_application.html</anchorfile>
      <anchor>afef88e4bc73a6f35379ee6c58ced26a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>LayerStack</type>
      <name>m_LayerStack</name>
      <anchorfile>class_real_engine_1_1_application.html</anchorfile>
      <anchor>aa66d5b21d932a786daee236eeb35cf0d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>Window</type>
      <name>m_Window</name>
      <anchorfile>class_real_engine_1_1_application.html</anchorfile>
      <anchor>a032a789ebf2616027b843bbaa18f02f5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>bool</type>
      <name>m_Running</name>
      <anchorfile>class_real_engine_1_1_application.html</anchorfile>
      <anchor>a0c6c05598bf66b864a41a55148693ffe</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private" static="yes">
      <type>static Application *</type>
      <name>s_Instance</name>
      <anchorfile>class_real_engine_1_1_application.html</anchorfile>
      <anchor>af75de12940e8339634c6100091621d34</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>RealEngine::ApplicationCommandLineArgs</name>
    <filename>struct_real_engine_1_1_application_command_line_args.html</filename>
    <member kind="function">
      <type>const char *</type>
      <name>operator[]</name>
      <anchorfile>struct_real_engine_1_1_application_command_line_args.html</anchorfile>
      <anchor>ab63f68ad91518510ab6ca91d2390bf43</anchor>
      <arglist>(int index) const</arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>Count</name>
      <anchorfile>struct_real_engine_1_1_application_command_line_args.html</anchorfile>
      <anchor>a0f239f0add39d1cea883cab38b0548c2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>char **</type>
      <name>Args</name>
      <anchorfile>struct_real_engine_1_1_application_command_line_args.html</anchorfile>
      <anchor>a5bea63ca226b5d32c5e1d514b1b296cd</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>RealEngine::ApplicationSpecification</name>
    <filename>struct_real_engine_1_1_application_specification.html</filename>
    <member kind="variable">
      <type>std::string</type>
      <name>Name</name>
      <anchorfile>struct_real_engine_1_1_application_specification.html</anchorfile>
      <anchor>afff1107e1b6f610afee333826e50a897</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>ApplicationCommandLineArgs</type>
      <name>CommandLineArgs</name>
      <anchorfile>struct_real_engine_1_1_application_specification.html</anchorfile>
      <anchor>abddb19019cecb06ff6bf6a35e3889d90</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RealEngine::Utils::Buffer</name>
    <filename>class_real_engine_1_1_utils_1_1_buffer.html</filename>
    <member kind="function">
      <type></type>
      <name>Buffer</name>
      <anchorfile>class_real_engine_1_1_utils_1_1_buffer.html</anchorfile>
      <anchor>a63606f8ff7b0beea6b6bbb98a7d57518</anchor>
      <arglist>(BufferType type, uint32_t size)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Buffer</name>
      <anchorfile>class_real_engine_1_1_utils_1_1_buffer.html</anchorfile>
      <anchor>a08a1f1f86f6bff4a6f91535fa5bd9dbd</anchor>
      <arglist>(BufferType type, const void *data, uint32_t size)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Buffer</name>
      <anchorfile>class_real_engine_1_1_utils_1_1_buffer.html</anchorfile>
      <anchor>a9a08b690173ff05a9aa5156d7c4684f2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const char *</type>
      <name>GetName</name>
      <anchorfile>class_real_engine_1_1_utils_1_1_buffer.html</anchorfile>
      <anchor>ad152dc34d98469aa1d340377161bffed</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual std::string</type>
      <name>ToString</name>
      <anchorfile>class_real_engine_1_1_utils_1_1_buffer.html</anchorfile>
      <anchor>a33fad4c0a5af5f6ab4c6742475a4d826</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Bind</name>
      <anchorfile>class_real_engine_1_1_utils_1_1_buffer.html</anchorfile>
      <anchor>a724571b17733b238490285d08d070385</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Unbind</name>
      <anchorfile>class_real_engine_1_1_utils_1_1_buffer.html</anchorfile>
      <anchor>ab0a26dc9a9c282f9ac286b31392c6534</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetData</name>
      <anchorfile>class_real_engine_1_1_utils_1_1_buffer.html</anchorfile>
      <anchor>a5e5ff4cd5b65fa97769700191bf43259</anchor>
      <arglist>(void *data, uint32_t size, uint32_t offset=0)</arglist>
    </member>
    <member kind="function">
      <type>BufferType</type>
      <name>GetType</name>
      <anchorfile>class_real_engine_1_1_utils_1_1_buffer.html</anchorfile>
      <anchor>a810ccc0171d10b34de8a2c110a54f152</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>uint32_t</type>
      <name>GetSize</name>
      <anchorfile>class_real_engine_1_1_utils_1_1_buffer.html</anchorfile>
      <anchor>ab276c9758090e377d2eb52fb784299ed</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>uint32_t</type>
      <name>m_RendererID</name>
      <anchorfile>class_real_engine_1_1_utils_1_1_buffer.html</anchorfile>
      <anchor>a7ece394d706d732a2b75e1176ef38b5b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>uint32_t</type>
      <name>m_Size</name>
      <anchorfile>class_real_engine_1_1_utils_1_1_buffer.html</anchorfile>
      <anchor>a2d97f9249869d036a4f9b5f361ce1b7f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>BufferType</type>
      <name>m_Type</name>
      <anchorfile>class_real_engine_1_1_utils_1_1_buffer.html</anchorfile>
      <anchor>a4fe7024d10b2c0e5ed7e3708cd238a26</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>CreateBuffer</name>
      <anchorfile>class_real_engine_1_1_utils_1_1_buffer.html</anchorfile>
      <anchor>ada4439045bd4752be24db17108a80206</anchor>
      <arglist>(const void *data, uint32_t size)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>RealEngine::BufferAttribute</name>
    <filename>struct_real_engine_1_1_buffer_attribute.html</filename>
    <member kind="function">
      <type></type>
      <name>BufferAttribute</name>
      <anchorfile>struct_real_engine_1_1_buffer_attribute.html</anchorfile>
      <anchor>a016ccbb4c9ef1a73e2d835272b3252c4</anchor>
      <arglist>()=delete</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BufferAttribute</name>
      <anchorfile>struct_real_engine_1_1_buffer_attribute.html</anchorfile>
      <anchor>a14034a930929c8b85ebcd6a64207aa64</anchor>
      <arglist>(DataType type)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BufferAttribute</name>
      <anchorfile>struct_real_engine_1_1_buffer_attribute.html</anchorfile>
      <anchor>a3b84b896636aa3be3299cd6510c67b68</anchor>
      <arglist>(DataType type, uint32_t instanceDivisor)</arglist>
    </member>
    <member kind="variable">
      <type>DataType</type>
      <name>Type</name>
      <anchorfile>struct_real_engine_1_1_buffer_attribute.html</anchorfile>
      <anchor>a6c8538f022e6bf4ed8d2869e5978d98b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>InstanceDivisor</name>
      <anchorfile>struct_real_engine_1_1_buffer_attribute.html</anchorfile>
      <anchor>aa36b2e9c86c89d8f6d35c0eb7a4c1775</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint8_t</type>
      <name>Size</name>
      <anchorfile>struct_real_engine_1_1_buffer_attribute.html</anchorfile>
      <anchor>a9f103133b926abc35041f3ea0f321a13</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>Offset</name>
      <anchorfile>struct_real_engine_1_1_buffer_attribute.html</anchorfile>
      <anchor>a133089e0906acf4059ac4cda9d2ce4b5</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>RealEngine::BufferAttributes</name>
    <filename>struct_real_engine_1_1_buffer_attributes.html</filename>
    <member kind="function">
      <type></type>
      <name>BufferAttributes</name>
      <anchorfile>struct_real_engine_1_1_buffer_attributes.html</anchorfile>
      <anchor>adddeaa742c3b065db2f4fb92a64ad87b</anchor>
      <arglist>(std::initializer_list&lt; BufferAttribute &gt; vertexAttribs)</arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>Stride</name>
      <anchorfile>struct_real_engine_1_1_buffer_attributes.html</anchorfile>
      <anchor>a0a2bb134284f4a46e25f1529bc731c98</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; BufferAttribute &gt;</type>
      <name>m_VertexAttribs</name>
      <anchorfile>struct_real_engine_1_1_buffer_attributes.html</anchorfile>
      <anchor>a6fde519c1f24317e080c3fb7426914f3</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RealEngine::Camera</name>
    <filename>class_real_engine_1_1_camera.html</filename>
    <member kind="function">
      <type></type>
      <name>Camera</name>
      <anchorfile>class_real_engine_1_1_camera.html</anchorfile>
      <anchor>aa76ed5b05e752b67c3d07e9a106dc61a</anchor>
      <arglist>(const glm::mat4 &amp;projection)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Camera</name>
      <anchorfile>class_real_engine_1_1_camera.html</anchorfile>
      <anchor>a0819d6460aa1c4e88f76ed20fa600f45</anchor>
      <arglist>()=default</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Camera</name>
      <anchorfile>class_real_engine_1_1_camera.html</anchorfile>
      <anchor>af9d9e8a33c80abe24024cac45e239d08</anchor>
      <arglist>()=default</arglist>
    </member>
    <member kind="function">
      <type>const glm::mat4 &amp;</type>
      <name>GetProjection</name>
      <anchorfile>class_real_engine_1_1_camera.html</anchorfile>
      <anchor>abff3879da6cad9d9a5ae375f2a4fde24</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>glm::mat4</type>
      <name>m_Projection</name>
      <anchorfile>class_real_engine_1_1_camera.html</anchorfile>
      <anchor>a1b68f73c58300836cc6e3692c1adb46e</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>quill::Codec&lt; glm::mat&lt; C, R, T, Q &gt; &gt;</name>
    <filename>structquill_1_1_codec_3_01glm_1_1mat_3_01_c_00_01_r_00_01_t_00_01_q_01_4_01_4.html</filename>
    <templarg>glm::length_t C</templarg>
    <templarg>glm::length_t R</templarg>
    <templarg>typename T</templarg>
    <templarg>glm::qualifier Q</templarg>
  </compound>
  <compound kind="struct">
    <name>quill::Codec&lt; glm::qua&lt; T, Q &gt; &gt;</name>
    <filename>structquill_1_1_codec_3_01glm_1_1qua_3_01_t_00_01_q_01_4_01_4.html</filename>
    <templarg>typename T</templarg>
    <templarg>glm::qualifier Q</templarg>
  </compound>
  <compound kind="struct">
    <name>quill::Codec&lt; glm::vec&lt; L, T, Q &gt; &gt;</name>
    <filename>structquill_1_1_codec_3_01glm_1_1vec_3_01_l_00_01_t_00_01_q_01_4_01_4.html</filename>
    <templarg>glm::length_t L</templarg>
    <templarg>typename T</templarg>
    <templarg>glm::qualifier Q</templarg>
  </compound>
  <compound kind="struct">
    <name>quill::Codec&lt; ryml::csubstr &gt;</name>
    <filename>structquill_1_1_codec_3_01ryml_1_1csubstr_01_4.html</filename>
  </compound>
  <compound kind="struct">
    <name>quill::Codec&lt; std::filesystem::path &gt;</name>
    <filename>structquill_1_1_codec_3_01std_1_1filesystem_1_1path_01_4.html</filename>
  </compound>
  <compound kind="class">
    <name>RealEngine::CommandBuffer</name>
    <filename>class_real_engine_1_1_command_buffer.html</filename>
    <base>RealEngine::Utils::Buffer</base>
  </compound>
  <compound kind="class">
    <name>RealEngine::DataType</name>
    <filename>class_real_engine_1_1_data_type.html</filename>
    <member kind="enumeration">
      <type></type>
      <name>Type</name>
      <anchorfile>class_real_engine_1_1_data_type.html</anchorfile>
      <anchor>a1cd14248968ecc2b47a9c66790bf7ae1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Float</name>
      <anchorfile>class_real_engine_1_1_data_type.html</anchorfile>
      <anchor>a1cd14248968ecc2b47a9c66790bf7ae1abf1c3029ac6f4f7f0b0a57ca3daab156</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Float2</name>
      <anchorfile>class_real_engine_1_1_data_type.html</anchorfile>
      <anchor>a1cd14248968ecc2b47a9c66790bf7ae1ac2e11bb91cafe6b64c5c7e42289a3627</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Float3</name>
      <anchorfile>class_real_engine_1_1_data_type.html</anchorfile>
      <anchor>a1cd14248968ecc2b47a9c66790bf7ae1ab15f649278a2b6cb35fe69686736a680</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Float4</name>
      <anchorfile>class_real_engine_1_1_data_type.html</anchorfile>
      <anchor>a1cd14248968ecc2b47a9c66790bf7ae1a645b7de4dfea2bf294120ddccec50d22</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Uint</name>
      <anchorfile>class_real_engine_1_1_data_type.html</anchorfile>
      <anchor>a1cd14248968ecc2b47a9c66790bf7ae1a9839d80697a2bd02ef8549c8677dc6b8</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Uint2</name>
      <anchorfile>class_real_engine_1_1_data_type.html</anchorfile>
      <anchor>a1cd14248968ecc2b47a9c66790bf7ae1a0910e542f2788c4ba4b2bcef776097b6</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Uint3</name>
      <anchorfile>class_real_engine_1_1_data_type.html</anchorfile>
      <anchor>a1cd14248968ecc2b47a9c66790bf7ae1a10d6c5e38443fecb922a71f7ccec03cc</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Uint4</name>
      <anchorfile>class_real_engine_1_1_data_type.html</anchorfile>
      <anchor>a1cd14248968ecc2b47a9c66790bf7ae1ab6334d4a5790f9b3d1755b9796419a03</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Int</name>
      <anchorfile>class_real_engine_1_1_data_type.html</anchorfile>
      <anchor>a1cd14248968ecc2b47a9c66790bf7ae1a80af1a7d5f2481aa5614e3f618d61db9</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Int2</name>
      <anchorfile>class_real_engine_1_1_data_type.html</anchorfile>
      <anchor>a1cd14248968ecc2b47a9c66790bf7ae1a66ea4c80fa1c0ce03fa04aff74263b03</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Int3</name>
      <anchorfile>class_real_engine_1_1_data_type.html</anchorfile>
      <anchor>a1cd14248968ecc2b47a9c66790bf7ae1abb97bbe89ccfb1e108b643dfe109e9ab</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Int4</name>
      <anchorfile>class_real_engine_1_1_data_type.html</anchorfile>
      <anchor>a1cd14248968ecc2b47a9c66790bf7ae1af55a70a3a47fd9fabe2684718cc0a6d4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Undefined</name>
      <anchorfile>class_real_engine_1_1_data_type.html</anchorfile>
      <anchor>a1cd14248968ecc2b47a9c66790bf7ae1a4154ae608a2319c545be16a06a8d16f0</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Float</name>
      <anchorfile>class_real_engine_1_1_data_type.html</anchorfile>
      <anchor>a1cd14248968ecc2b47a9c66790bf7ae1abf1c3029ac6f4f7f0b0a57ca3daab156</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Float2</name>
      <anchorfile>class_real_engine_1_1_data_type.html</anchorfile>
      <anchor>a1cd14248968ecc2b47a9c66790bf7ae1ac2e11bb91cafe6b64c5c7e42289a3627</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Float3</name>
      <anchorfile>class_real_engine_1_1_data_type.html</anchorfile>
      <anchor>a1cd14248968ecc2b47a9c66790bf7ae1ab15f649278a2b6cb35fe69686736a680</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Float4</name>
      <anchorfile>class_real_engine_1_1_data_type.html</anchorfile>
      <anchor>a1cd14248968ecc2b47a9c66790bf7ae1a645b7de4dfea2bf294120ddccec50d22</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Uint</name>
      <anchorfile>class_real_engine_1_1_data_type.html</anchorfile>
      <anchor>a1cd14248968ecc2b47a9c66790bf7ae1a9839d80697a2bd02ef8549c8677dc6b8</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Uint2</name>
      <anchorfile>class_real_engine_1_1_data_type.html</anchorfile>
      <anchor>a1cd14248968ecc2b47a9c66790bf7ae1a0910e542f2788c4ba4b2bcef776097b6</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Uint3</name>
      <anchorfile>class_real_engine_1_1_data_type.html</anchorfile>
      <anchor>a1cd14248968ecc2b47a9c66790bf7ae1a10d6c5e38443fecb922a71f7ccec03cc</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Uint4</name>
      <anchorfile>class_real_engine_1_1_data_type.html</anchorfile>
      <anchor>a1cd14248968ecc2b47a9c66790bf7ae1ab6334d4a5790f9b3d1755b9796419a03</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Int</name>
      <anchorfile>class_real_engine_1_1_data_type.html</anchorfile>
      <anchor>a1cd14248968ecc2b47a9c66790bf7ae1a80af1a7d5f2481aa5614e3f618d61db9</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Int2</name>
      <anchorfile>class_real_engine_1_1_data_type.html</anchorfile>
      <anchor>a1cd14248968ecc2b47a9c66790bf7ae1a66ea4c80fa1c0ce03fa04aff74263b03</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Int3</name>
      <anchorfile>class_real_engine_1_1_data_type.html</anchorfile>
      <anchor>a1cd14248968ecc2b47a9c66790bf7ae1abb97bbe89ccfb1e108b643dfe109e9ab</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Int4</name>
      <anchorfile>class_real_engine_1_1_data_type.html</anchorfile>
      <anchor>a1cd14248968ecc2b47a9c66790bf7ae1af55a70a3a47fd9fabe2684718cc0a6d4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Undefined</name>
      <anchorfile>class_real_engine_1_1_data_type.html</anchorfile>
      <anchor>a1cd14248968ecc2b47a9c66790bf7ae1a4154ae608a2319c545be16a06a8d16f0</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DataType</name>
      <anchorfile>class_real_engine_1_1_data_type.html</anchorfile>
      <anchor>ad97f0dc5dd8c951d07cbac462a833d78</anchor>
      <arglist>()=delete</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>DataType</name>
      <anchorfile>class_real_engine_1_1_data_type.html</anchorfile>
      <anchor>a8b555bf17b9e3b32e7d3b919dfbec289</anchor>
      <arglist>(Type type)</arglist>
    </member>
    <member kind="function">
      <type>Type</type>
      <name>GetType</name>
      <anchorfile>class_real_engine_1_1_data_type.html</anchorfile>
      <anchor>aa087ce8a116e8077ab78f17086c89bfd</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>uint8_t</type>
      <name>GetTypeElementCount</name>
      <anchorfile>class_real_engine_1_1_data_type.html</anchorfile>
      <anchor>a24ae57661c1806900528a0455d3d94ae</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>uint8_t</type>
      <name>GetTypeSizeOf</name>
      <anchorfile>class_real_engine_1_1_data_type.html</anchorfile>
      <anchor>ae313ae98bc5a9374d957dee3e9a2e54c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>GLint</type>
      <name>GetGLType</name>
      <anchorfile>class_real_engine_1_1_data_type.html</anchorfile>
      <anchor>a9c0cba193d498fd6e4cb536a13afc38b</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>Type</type>
      <name>m_Type</name>
      <anchorfile>class_real_engine_1_1_data_type.html</anchorfile>
      <anchor>a42a3ace61c71bc740c15aa40efd644b5</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RealEngine::EditorCamera</name>
    <filename>class_real_engine_1_1_editor_camera.html</filename>
    <base>RealEngine::Camera</base>
    <member kind="function">
      <type></type>
      <name>EditorCamera</name>
      <anchorfile>class_real_engine_1_1_editor_camera.html</anchorfile>
      <anchor>a088b0e19917881b05a15bb436218a74e</anchor>
      <arglist>(float fov, float aspectRatio, float nearClip, float farClip)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>EditorCamera</name>
      <anchorfile>class_real_engine_1_1_editor_camera.html</anchorfile>
      <anchor>af6509a7096641830aba4261698686050</anchor>
      <arglist>()=default</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>OnUpdate</name>
      <anchorfile>class_real_engine_1_1_editor_camera.html</anchorfile>
      <anchor>a05cc0ddffe2a1c69a229a3ce44e6806b</anchor>
      <arglist>(float deltaTime)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>OnEvent</name>
      <anchorfile>class_real_engine_1_1_editor_camera.html</anchorfile>
      <anchor>ae9e0823690c5e38d4ae70aa0da453673</anchor>
      <arglist>(Event &amp;e)</arglist>
    </member>
    <member kind="function">
      <type>float</type>
      <name>GetDistance</name>
      <anchorfile>class_real_engine_1_1_editor_camera.html</anchorfile>
      <anchor>ae44449d3d27eb40bd642ad03eea2411b</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetDistance</name>
      <anchorfile>class_real_engine_1_1_editor_camera.html</anchorfile>
      <anchor>a78bd5b1b29b4bd9b66dca5e8c7bf5b2d</anchor>
      <arglist>(float distance)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetViewportSize</name>
      <anchorfile>class_real_engine_1_1_editor_camera.html</anchorfile>
      <anchor>a91c9a9ca7bd3a6cce131c78525ec06cd</anchor>
      <arglist>(float width, float height)</arglist>
    </member>
    <member kind="function">
      <type>const glm::mat4 &amp;</type>
      <name>GetViewMatrix</name>
      <anchorfile>class_real_engine_1_1_editor_camera.html</anchorfile>
      <anchor>a2673d06e9c013f60559458b4247fd59d</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>glm::mat4</type>
      <name>GetViewProjection</name>
      <anchorfile>class_real_engine_1_1_editor_camera.html</anchorfile>
      <anchor>ab5289720d817279ca76c65b1ff351116</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>glm::vec3</type>
      <name>GetUpDirection</name>
      <anchorfile>class_real_engine_1_1_editor_camera.html</anchorfile>
      <anchor>a2f0414abb651e1b59cf16772f62689d7</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>glm::vec3</type>
      <name>GetRightDirection</name>
      <anchorfile>class_real_engine_1_1_editor_camera.html</anchorfile>
      <anchor>ade9cb70cc9ff03cb5d33c0b9c07d47a8</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>glm::vec3</type>
      <name>GetForwardDirection</name>
      <anchorfile>class_real_engine_1_1_editor_camera.html</anchorfile>
      <anchor>a3860551ae3f6f49d1ec3ef1d04b9a465</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>const glm::vec3 &amp;</type>
      <name>GetPosition</name>
      <anchorfile>class_real_engine_1_1_editor_camera.html</anchorfile>
      <anchor>a48e7e0dd4ac31b3256279eac4a12f4e5</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>glm::quat</type>
      <name>GetOrientation</name>
      <anchorfile>class_real_engine_1_1_editor_camera.html</anchorfile>
      <anchor>a6ed929e3f2f3e731d9a8d87e87c823e9</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>float</type>
      <name>GetPitch</name>
      <anchorfile>class_real_engine_1_1_editor_camera.html</anchorfile>
      <anchor>afbf5516363171f20e940b27a97741987</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>float</type>
      <name>GetYaw</name>
      <anchorfile>class_real_engine_1_1_editor_camera.html</anchorfile>
      <anchor>a64dbfd093801bf2328e3f1e04deff776</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>UpdateProjection</name>
      <anchorfile>class_real_engine_1_1_editor_camera.html</anchorfile>
      <anchor>a6c7d3710faf6eacb723a24bf1031bfd4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>UpdateView</name>
      <anchorfile>class_real_engine_1_1_editor_camera.html</anchorfile>
      <anchor>ae3a97d6f0aa1f56ea02b4d350b5db00f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>OnMouseScroll</name>
      <anchorfile>class_real_engine_1_1_editor_camera.html</anchorfile>
      <anchor>a0106e246f4ebfca3bb66aa67ac0324d3</anchor>
      <arglist>(MouseScrolledEvent &amp;e)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>MousePan</name>
      <anchorfile>class_real_engine_1_1_editor_camera.html</anchorfile>
      <anchor>ae73e7e74c5a0f2115bde0fbb06ac6280</anchor>
      <arglist>(const glm::vec2 &amp;delta)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>MouseRotate</name>
      <anchorfile>class_real_engine_1_1_editor_camera.html</anchorfile>
      <anchor>a5c2424096791e543f4b4a1f5c90a499f</anchor>
      <arglist>(const glm::vec2 &amp;delta)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>MouseZoom</name>
      <anchorfile>class_real_engine_1_1_editor_camera.html</anchorfile>
      <anchor>ae8f6a3fd8ae6f9cb963c3c4c623b0022</anchor>
      <arglist>(float delta)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>glm::vec3</type>
      <name>CalculatePosition</name>
      <anchorfile>class_real_engine_1_1_editor_camera.html</anchorfile>
      <anchor>a9b6734017b9da60078a430d3e9094e03</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function" protection="private">
      <type>std::pair&lt; float, float &gt;</type>
      <name>PanSpeed</name>
      <anchorfile>class_real_engine_1_1_editor_camera.html</anchorfile>
      <anchor>a4d20c44c68fcad7e32201cf1f72c5d38</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function" protection="private">
      <type>float</type>
      <name>RotationSpeed</name>
      <anchorfile>class_real_engine_1_1_editor_camera.html</anchorfile>
      <anchor>a0ef73a0866868982b95189b8b274b075</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function" protection="private">
      <type>float</type>
      <name>ZoomSpeed</name>
      <anchorfile>class_real_engine_1_1_editor_camera.html</anchorfile>
      <anchor>a0c8efc3efc4bb43c6063396d8ca783af</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>float</type>
      <name>m_FOV</name>
      <anchorfile>class_real_engine_1_1_editor_camera.html</anchorfile>
      <anchor>a47ebad655c1aef2f2ddbf94180c29846</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>float</type>
      <name>m_AspectRatio</name>
      <anchorfile>class_real_engine_1_1_editor_camera.html</anchorfile>
      <anchor>a1dccfed0a27cbdc35b7c4fbfdc93b3c0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>float</type>
      <name>m_NearClip</name>
      <anchorfile>class_real_engine_1_1_editor_camera.html</anchorfile>
      <anchor>a3991b2b29f6260c70b3be777eab0a9d6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>float</type>
      <name>m_FarClip</name>
      <anchorfile>class_real_engine_1_1_editor_camera.html</anchorfile>
      <anchor>af774542802cf154fbc3a6a4c638e4a43</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>glm::mat4</type>
      <name>m_ViewMatrix</name>
      <anchorfile>class_real_engine_1_1_editor_camera.html</anchorfile>
      <anchor>aa24fb1fb008fa823f96ca2efcba24ccb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>glm::vec3</type>
      <name>m_Position</name>
      <anchorfile>class_real_engine_1_1_editor_camera.html</anchorfile>
      <anchor>a417d07a83df5aa0bc66e192fc9eab1ee</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>glm::vec3</type>
      <name>m_FocalPoint</name>
      <anchorfile>class_real_engine_1_1_editor_camera.html</anchorfile>
      <anchor>a603070d14b4607bbaec86ecfb80df6e3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>glm::vec2</type>
      <name>m_InitialMousePosition</name>
      <anchorfile>class_real_engine_1_1_editor_camera.html</anchorfile>
      <anchor>acf7df59a6385319c433482e0268883b4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>float</type>
      <name>m_Distance</name>
      <anchorfile>class_real_engine_1_1_editor_camera.html</anchorfile>
      <anchor>a90aedefc9bf573ff1d3201211f5bcee1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>float</type>
      <name>m_Pitch</name>
      <anchorfile>class_real_engine_1_1_editor_camera.html</anchorfile>
      <anchor>a9680272266a7cea00b1dadc773932c6f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>float</type>
      <name>m_Yaw</name>
      <anchorfile>class_real_engine_1_1_editor_camera.html</anchorfile>
      <anchor>a241ec11d5f3e813605a60f96e4328311</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>float</type>
      <name>m_ViewportWidth</name>
      <anchorfile>class_real_engine_1_1_editor_camera.html</anchorfile>
      <anchor>a49adae5a71a76c6757904d0c973f5515</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>float</type>
      <name>m_ViewportHeight</name>
      <anchorfile>class_real_engine_1_1_editor_camera.html</anchorfile>
      <anchor>a3f953d02826aed85098482058835c796</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RealEngine::Event</name>
    <filename>class_real_engine_1_1_event.html</filename>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Event</name>
      <anchorfile>class_real_engine_1_1_event.html</anchorfile>
      <anchor>afe477721b308e06bf6348130ddb79d9c</anchor>
      <arglist>()=default</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const char *</type>
      <name>GetName</name>
      <anchorfile>class_real_engine_1_1_event.html</anchorfile>
      <anchor>af9ed8fe98fddf9a143296d654bfdfe56</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual std::string</type>
      <name>ToString</name>
      <anchorfile>class_real_engine_1_1_event.html</anchorfile>
      <anchor>aef3acdc06e4d43ba5eb716bb9501fb20</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual EventType</type>
      <name>GetEventType</name>
      <anchorfile>class_real_engine_1_1_event.html</anchorfile>
      <anchor>a5aa7f3bff725e497765f0740f3ed0860</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>Handled</name>
      <anchorfile>class_real_engine_1_1_event.html</anchorfile>
      <anchor>a26e6312b59e84e004788fbbd245d5dea</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RealEngine::EventDispatcher</name>
    <filename>class_real_engine_1_1_event_dispatcher.html</filename>
    <member kind="function">
      <type></type>
      <name>EventDispatcher</name>
      <anchorfile>class_real_engine_1_1_event_dispatcher.html</anchorfile>
      <anchor>a3e1f184d3f932a85d874603194e5b122</anchor>
      <arglist>(Event &amp;event)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Dispatch</name>
      <anchorfile>class_real_engine_1_1_event_dispatcher.html</anchorfile>
      <anchor>a34d2d5543e872c08d2778002a2cef798</anchor>
      <arglist>(const F &amp;func)</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>Event &amp;</type>
      <name>m_Event</name>
      <anchorfile>class_real_engine_1_1_event_dispatcher.html</anchorfile>
      <anchor>a1908a03d5e00d46b7f49708812f360f8</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fmtquill::formatter&lt; glm::mat&lt; C, R, T, Q &gt; &gt;</name>
    <filename>structfmtquill_1_1formatter_3_01glm_1_1mat_3_01_c_00_01_r_00_01_t_00_01_q_01_4_01_4.html</filename>
    <templarg>glm::length_t C</templarg>
    <templarg>glm::length_t R</templarg>
    <templarg>typename T</templarg>
    <templarg>glm::qualifier Q</templarg>
    <member kind="function">
      <type>constexpr auto</type>
      <name>parse</name>
      <anchorfile>structfmtquill_1_1formatter_3_01glm_1_1mat_3_01_c_00_01_r_00_01_t_00_01_q_01_4_01_4.html</anchorfile>
      <anchor>a60a13e321b705cd607c938721d73bbf7</anchor>
      <arglist>(format_parse_context &amp;ctx)</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>format</name>
      <anchorfile>structfmtquill_1_1formatter_3_01glm_1_1mat_3_01_c_00_01_r_00_01_t_00_01_q_01_4_01_4.html</anchorfile>
      <anchor>a196973acc97080dc9257f53eb1c64e54</anchor>
      <arglist>(::glm::mat&lt; C, R, T, Q &gt; const &amp;matrix, format_context &amp;ctx) const</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fmtquill::formatter&lt; glm::qua&lt; T, Q &gt; &gt;</name>
    <filename>structfmtquill_1_1formatter_3_01glm_1_1qua_3_01_t_00_01_q_01_4_01_4.html</filename>
    <templarg>typename T</templarg>
    <templarg>glm::qualifier Q</templarg>
    <member kind="function">
      <type>constexpr auto</type>
      <name>parse</name>
      <anchorfile>structfmtquill_1_1formatter_3_01glm_1_1qua_3_01_t_00_01_q_01_4_01_4.html</anchorfile>
      <anchor>aef7e0216c4961967c0cca47bbb67d536</anchor>
      <arglist>(format_parse_context &amp;ctx)</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>format</name>
      <anchorfile>structfmtquill_1_1formatter_3_01glm_1_1qua_3_01_t_00_01_q_01_4_01_4.html</anchorfile>
      <anchor>a6882c0a05ac750bf98cf2c3707f33e63</anchor>
      <arglist>(::glm::qua&lt; T, Q &gt; const &amp;quaternion, format_context &amp;ctx) const</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fmtquill::formatter&lt; glm::vec&lt; L, T, Q &gt; &gt;</name>
    <filename>structfmtquill_1_1formatter_3_01glm_1_1vec_3_01_l_00_01_t_00_01_q_01_4_01_4.html</filename>
    <templarg>glm::length_t L</templarg>
    <templarg>typename T</templarg>
    <templarg>glm::qualifier Q</templarg>
    <member kind="function">
      <type>constexpr auto</type>
      <name>parse</name>
      <anchorfile>structfmtquill_1_1formatter_3_01glm_1_1vec_3_01_l_00_01_t_00_01_q_01_4_01_4.html</anchorfile>
      <anchor>a352d567e6d86c6341fe3ac008d86810a</anchor>
      <arglist>(format_parse_context &amp;ctx)</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>format</name>
      <anchorfile>structfmtquill_1_1formatter_3_01glm_1_1vec_3_01_l_00_01_t_00_01_q_01_4_01_4.html</anchorfile>
      <anchor>a19807fd25d542d1bfc81896fd524fb37</anchor>
      <arglist>(::glm::vec&lt; L, T, Q &gt; const &amp;vertex, format_context &amp;ctx) const</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fmtquill::formatter&lt; ryml::csubstr &gt;</name>
    <filename>structfmtquill_1_1formatter_3_01ryml_1_1csubstr_01_4.html</filename>
    <member kind="function">
      <type>constexpr auto</type>
      <name>parse</name>
      <anchorfile>structfmtquill_1_1formatter_3_01ryml_1_1csubstr_01_4.html</anchorfile>
      <anchor>a6e3ecf5aeeb379ed004f1e902a37b9ad</anchor>
      <arglist>(format_parse_context &amp;ctx)</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>format</name>
      <anchorfile>structfmtquill_1_1formatter_3_01ryml_1_1csubstr_01_4.html</anchorfile>
      <anchor>a8da7347410bb1d0a91cc4971e8048ffb</anchor>
      <arglist>(::ryml::csubstr const &amp;str, format_context &amp;ctx) const</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fmtquill::formatter&lt; std::filesystem::path &gt;</name>
    <filename>structfmtquill_1_1formatter_3_01std_1_1filesystem_1_1path_01_4.html</filename>
    <member kind="function">
      <type>constexpr auto</type>
      <name>parse</name>
      <anchorfile>structfmtquill_1_1formatter_3_01std_1_1filesystem_1_1path_01_4.html</anchorfile>
      <anchor>a380c70614edde6a54049b8d722bad1b6</anchor>
      <arglist>(format_parse_context &amp;ctx)</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>format</name>
      <anchorfile>structfmtquill_1_1formatter_3_01std_1_1filesystem_1_1path_01_4.html</anchorfile>
      <anchor>a29119ea45e126b0c53acdc45f2f3dca5</anchor>
      <arglist>(::std::filesystem::path const &amp;path, format_context &amp;ctx) const</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RealEngine::Framebuffer</name>
    <filename>class_real_engine_1_1_framebuffer.html</filename>
    <member kind="function">
      <type></type>
      <name>Framebuffer</name>
      <anchorfile>class_real_engine_1_1_framebuffer.html</anchorfile>
      <anchor>afa18e54fd725ff61352b1a2889c41f21</anchor>
      <arglist>(const FramebufferSpecification &amp;specs)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Framebuffer</name>
      <anchorfile>class_real_engine_1_1_framebuffer.html</anchorfile>
      <anchor>aff74609188ebc0c8840586fe76734ba4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Bind</name>
      <anchorfile>class_real_engine_1_1_framebuffer.html</anchorfile>
      <anchor>af5adb44b631d35d44854a422ccc4b6e3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Unbind</name>
      <anchorfile>class_real_engine_1_1_framebuffer.html</anchorfile>
      <anchor>a4161e56eea18339a9ac20de188e93bb9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Resize</name>
      <anchorfile>class_real_engine_1_1_framebuffer.html</anchorfile>
      <anchor>aef0a3c258a9ee53da4a258c191b17059</anchor>
      <arglist>(uint32_t width, uint32_t height)</arglist>
    </member>
    <member kind="function">
      <type>uint32_t</type>
      <name>GetAttachmentRendererID</name>
      <anchorfile>class_real_engine_1_1_framebuffer.html</anchorfile>
      <anchor>a11d7c4476ecf6c3592e40052df68cc10</anchor>
      <arglist>(uint32_t index=0) const</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>Invalidate</name>
      <anchorfile>class_real_engine_1_1_framebuffer.html</anchorfile>
      <anchor>a816d9d73dc51cd5bd662686aca29f781</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>uint32_t</type>
      <name>m_FramebufferID</name>
      <anchorfile>class_real_engine_1_1_framebuffer.html</anchorfile>
      <anchor>a4279aaf9138ee275736d5769d4188a25</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>FramebufferSpecification</type>
      <name>m_Specification</name>
      <anchorfile>class_real_engine_1_1_framebuffer.html</anchorfile>
      <anchor>ad914650f17439321906ff54eea7f8414</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>std::vector&lt; uint32_t &gt;</type>
      <name>m_Attachments</name>
      <anchorfile>class_real_engine_1_1_framebuffer.html</anchorfile>
      <anchor>a3f9ac4bf2898f50f905b459284108abd</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>RealEngine::FramebufferAttachmentSpecification</name>
    <filename>struct_real_engine_1_1_framebuffer_attachment_specification.html</filename>
    <member kind="function">
      <type></type>
      <name>FramebufferAttachmentSpecification</name>
      <anchorfile>struct_real_engine_1_1_framebuffer_attachment_specification.html</anchorfile>
      <anchor>a9ac84ca43c51cd65809a217eb70005f1</anchor>
      <arglist>(std::initializer_list&lt; FramebufferTextureSpecification &gt; attachments)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>FramebufferAttachmentSpecification</name>
      <anchorfile>struct_real_engine_1_1_framebuffer_attachment_specification.html</anchorfile>
      <anchor>a9933c70ce3a2e617dda661f79dd77d06</anchor>
      <arglist>()=default</arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; FramebufferTextureSpecification &gt;</type>
      <name>Attachments</name>
      <anchorfile>struct_real_engine_1_1_framebuffer_attachment_specification.html</anchorfile>
      <anchor>a57a696138b3da4d3f60df72716863b11</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>RealEngine::FramebufferSpecification</name>
    <filename>struct_real_engine_1_1_framebuffer_specification.html</filename>
    <member kind="variable">
      <type>FramebufferAttachmentSpecification</type>
      <name>Attachments</name>
      <anchorfile>struct_real_engine_1_1_framebuffer_specification.html</anchorfile>
      <anchor>af11154fc7e7c63087998f56a24f897ab</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>Width</name>
      <anchorfile>struct_real_engine_1_1_framebuffer_specification.html</anchorfile>
      <anchor>a8b561bba3974721560896e6b03a79dd9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>Height</name>
      <anchorfile>struct_real_engine_1_1_framebuffer_specification.html</anchorfile>
      <anchor>aebd2b985bfc0a74af89460bda81d2534</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>RealEngine::FramebufferTextureSpecification</name>
    <filename>struct_real_engine_1_1_framebuffer_texture_specification.html</filename>
    <member kind="function">
      <type></type>
      <name>FramebufferTextureSpecification</name>
      <anchorfile>struct_real_engine_1_1_framebuffer_texture_specification.html</anchorfile>
      <anchor>aaae5541c5dbb1899401cd1c459691ce8</anchor>
      <arglist>(FramebufferTextureFormat format)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>FramebufferTextureSpecification</name>
      <anchorfile>struct_real_engine_1_1_framebuffer_texture_specification.html</anchorfile>
      <anchor>aaddc7c23fede622fc6ba2943ffd6618c</anchor>
      <arglist>()=default</arglist>
    </member>
    <member kind="variable">
      <type>FramebufferTextureFormat</type>
      <name>TextureFormat</name>
      <anchorfile>struct_real_engine_1_1_framebuffer_texture_specification.html</anchorfile>
      <anchor>afa1e33721bf2c34bde3879a64d6b11e0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RealEngine::GeneralManager</name>
    <filename>class_real_engine_1_1_general_manager.html</filename>
    <templarg>typename T</templarg>
    <member kind="function">
      <type></type>
      <name>GeneralManager</name>
      <anchorfile>class_real_engine_1_1_general_manager.html</anchorfile>
      <anchor>a099016c20bfc80a11412a20d7cdefc4b</anchor>
      <arglist>()=delete</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Ref&lt; T &gt;</type>
      <name>LoadResource</name>
      <anchorfile>class_real_engine_1_1_general_manager.html</anchorfile>
      <anchor>af21973003eecaa1a2886f458483259ac</anchor>
      <arglist>(const std::filesystem::path &amp;path)</arglist>
    </member>
    <member kind="variable" protection="private" static="yes">
      <type>static std::unordered_map&lt; PathHash, Weak_Ref&lt; T &gt; &gt;</type>
      <name>s_Resources</name>
      <anchorfile>class_real_engine_1_1_general_manager.html</anchorfile>
      <anchor>aa1e54e4e11d9adae55e92776784a9e43</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>std::hash&lt; RealEngine::PathHash &gt;</name>
    <filename>structstd_1_1hash_3_01_real_engine_1_1_path_hash_01_4.html</filename>
    <member kind="function">
      <type>std::size_t</type>
      <name>operator()</name>
      <anchorfile>structstd_1_1hash_3_01_real_engine_1_1_path_hash_01_4.html</anchorfile>
      <anchor>aa958199722024701bf9d06b511f772ec</anchor>
      <arglist>(const RealEngine::PathHash &amp;stringHash) const</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>std::hash&lt; RealEngine::StringHash &gt;</name>
    <filename>structstd_1_1hash_3_01_real_engine_1_1_string_hash_01_4.html</filename>
    <member kind="function">
      <type>std::size_t</type>
      <name>operator()</name>
      <anchorfile>structstd_1_1hash_3_01_real_engine_1_1_string_hash_01_4.html</anchorfile>
      <anchor>afa4e6b5cec1c3e46147137870f337026</anchor>
      <arglist>(const RealEngine::StringHash &amp;stringHash) const</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>std::hash&lt; RealEngine::UUID &gt;</name>
    <filename>structstd_1_1hash_3_01_real_engine_1_1_u_u_i_d_01_4.html</filename>
    <member kind="function">
      <type>std::size_t</type>
      <name>operator()</name>
      <anchorfile>structstd_1_1hash_3_01_real_engine_1_1_u_u_i_d_01_4.html</anchorfile>
      <anchor>ac926282dbf50c002707ab4d4004c7ff3</anchor>
      <arglist>(const RealEngine::UUID &amp;uuid) const</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RealEngine::ImGuiLayer</name>
    <filename>class_real_engine_1_1_im_gui_layer.html</filename>
    <base>RealEngine::Layer</base>
    <member kind="function">
      <type></type>
      <name>ImGuiLayer</name>
      <anchorfile>class_real_engine_1_1_im_gui_layer.html</anchorfile>
      <anchor>ac5db144a0783d4e168345e3c1957925d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>OnAttach</name>
      <anchorfile>class_real_engine_1_1_im_gui_layer.html</anchorfile>
      <anchor>a4e8a7f241bb6a43dbeaff774b4e8c465</anchor>
      <arglist>() override</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>OnDetach</name>
      <anchorfile>class_real_engine_1_1_im_gui_layer.html</anchorfile>
      <anchor>a36f99f1b422d072c8574f29177b7cce0</anchor>
      <arglist>() override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetScale</name>
      <anchorfile>class_real_engine_1_1_im_gui_layer.html</anchorfile>
      <anchor>a63d4d55d2275270f65cfce43170a5823</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Begin</name>
      <anchorfile>class_real_engine_1_1_im_gui_layer.html</anchorfile>
      <anchor>a477dc5651747b543f30cc7078362da00</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>End</name>
      <anchorfile>class_real_engine_1_1_im_gui_layer.html</anchorfile>
      <anchor>ac5afc89c5287731eab873a647023c638</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RealEngine::IndexBuffer</name>
    <filename>class_real_engine_1_1_index_buffer.html</filename>
    <base>RealEngine::Utils::Buffer</base>
    <member kind="function">
      <type></type>
      <name>IndexBuffer</name>
      <anchorfile>class_real_engine_1_1_index_buffer.html</anchorfile>
      <anchor>a2764d4ba90380f3869b970dbcaf8a918</anchor>
      <arglist>(uint32_t count)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>IndexBuffer</name>
      <anchorfile>class_real_engine_1_1_index_buffer.html</anchorfile>
      <anchor>a14e0006b528dfab3d7d92475ff5629e1</anchor>
      <arglist>(const uint32_t *data, uint32_t count)</arglist>
    </member>
    <member kind="function">
      <type>uint32_t</type>
      <name>GetCount</name>
      <anchorfile>class_real_engine_1_1_index_buffer.html</anchorfile>
      <anchor>a7cd25d4937610a9fdfe903e06810ebec</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Ref&lt; IndexBuffer &gt;</type>
      <name>Create</name>
      <anchorfile>class_real_engine_1_1_index_buffer.html</anchorfile>
      <anchor>aef1faddf7c2f2ccca9cbb72eda5770be</anchor>
      <arglist>(uint32_t size)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Ref&lt; IndexBuffer &gt;</type>
      <name>Create</name>
      <anchorfile>class_real_engine_1_1_index_buffer.html</anchorfile>
      <anchor>a1abb1ff784e5072594191610eee431e7</anchor>
      <arglist>(const uint32_t *data, uint32_t size)</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>const uint32_t</type>
      <name>m_Count</name>
      <anchorfile>class_real_engine_1_1_index_buffer.html</anchorfile>
      <anchor>a88e3ff7f45d88cf879040197df6466ba</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RealEngine::Input</name>
    <filename>class_real_engine_1_1_input.html</filename>
    <member kind="function" static="yes">
      <type>static bool</type>
      <name>IsKeyPressed</name>
      <anchorfile>class_real_engine_1_1_input.html</anchorfile>
      <anchor>a26997d31ace88b2d0baab7c3d1f97063</anchor>
      <arglist>(KeyCode keycode)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static bool</type>
      <name>IsMouseButtonPressed</name>
      <anchorfile>class_real_engine_1_1_input.html</anchorfile>
      <anchor>a8e71ab812a4397c9206a49e8e38f373b</anchor>
      <arglist>(MouseCode button)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static std::pair&lt; float, float &gt;</type>
      <name>GetMousePosition</name>
      <anchorfile>class_real_engine_1_1_input.html</anchorfile>
      <anchor>afb1d45a07627883cd0f4666959a4ce45</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static float</type>
      <name>GetMouseX</name>
      <anchorfile>class_real_engine_1_1_input.html</anchorfile>
      <anchor>aa1aa003fdd0c7b1e42119cd6c2471755</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static float</type>
      <name>GetMouseY</name>
      <anchorfile>class_real_engine_1_1_input.html</anchorfile>
      <anchor>a80da87fc6483fe4002291616419a71aa</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RealEngine::KeyPressedEvent</name>
    <filename>class_real_engine_1_1_key_pressed_event.html</filename>
    <base>RealEngine::Event</base>
    <member kind="function">
      <type></type>
      <name>KeyPressedEvent</name>
      <anchorfile>class_real_engine_1_1_key_pressed_event.html</anchorfile>
      <anchor>aaaa75e9c1795b8f6881167a61087639d</anchor>
      <arglist>(const KeyCode keycode)</arglist>
    </member>
    <member kind="function">
      <type>KeyCode</type>
      <name>GetKeyCode</name>
      <anchorfile>class_real_engine_1_1_key_pressed_event.html</anchorfile>
      <anchor>a2963b763c072136a8bc2cd93178d8878</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>ToString</name>
      <anchorfile>class_real_engine_1_1_key_pressed_event.html</anchorfile>
      <anchor>a670f1e3713c7f33238fc4f747d515ef3</anchor>
      <arglist>() const override</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>const KeyCode</type>
      <name>m_KeyCode</name>
      <anchorfile>class_real_engine_1_1_key_pressed_event.html</anchorfile>
      <anchor>ac36f2f68d2c551800aeb1a491e2a35c0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RealEngine::KeyReleasedEvent</name>
    <filename>class_real_engine_1_1_key_released_event.html</filename>
    <base>RealEngine::Event</base>
    <member kind="function">
      <type></type>
      <name>KeyReleasedEvent</name>
      <anchorfile>class_real_engine_1_1_key_released_event.html</anchorfile>
      <anchor>adb87d9ce24ca100ca6c6af71a0b1ece8</anchor>
      <arglist>(const KeyCode keycode)</arglist>
    </member>
    <member kind="function">
      <type>KeyCode</type>
      <name>GetKeyCode</name>
      <anchorfile>class_real_engine_1_1_key_released_event.html</anchorfile>
      <anchor>a08f85ca60fdcbcfbf0e71dd8d08f9c44</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>ToString</name>
      <anchorfile>class_real_engine_1_1_key_released_event.html</anchorfile>
      <anchor>a012692bcafccd344589d8a2aace3c918</anchor>
      <arglist>() const override</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>const KeyCode</type>
      <name>m_KeyCode</name>
      <anchorfile>class_real_engine_1_1_key_released_event.html</anchorfile>
      <anchor>a97f84fd16cbe147417e62cbb9dbf665b</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RealEngine::Layer</name>
    <filename>class_real_engine_1_1_layer.html</filename>
    <member kind="function">
      <type></type>
      <name>Layer</name>
      <anchorfile>class_real_engine_1_1_layer.html</anchorfile>
      <anchor>a5b7cfe36016949c49b860dcfb34e17a2</anchor>
      <arglist>(const std::string &amp;name=&quot;Default Layer&quot;)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Layer</name>
      <anchorfile>class_real_engine_1_1_layer.html</anchorfile>
      <anchor>ab1dde6366bf49861574f0e91c2c56884</anchor>
      <arglist>()=default</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>OnAttach</name>
      <anchorfile>class_real_engine_1_1_layer.html</anchorfile>
      <anchor>a365fdc99684770703122207a1827abbd</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>OnDetach</name>
      <anchorfile>class_real_engine_1_1_layer.html</anchorfile>
      <anchor>a4b6a7c923bb21de0cbd78d315d68fc94</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>OnUpdate</name>
      <anchorfile>class_real_engine_1_1_layer.html</anchorfile>
      <anchor>ad453c9e7939a838c478e1473f50a53be</anchor>
      <arglist>(const float deltaTime)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>OnImGui</name>
      <anchorfile>class_real_engine_1_1_layer.html</anchorfile>
      <anchor>a6769c0710bf116f6f3f3e3da153645cb</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>OnEvent</name>
      <anchorfile>class_real_engine_1_1_layer.html</anchorfile>
      <anchor>a03e12ab4b8392a662c936f43e3fc7c42</anchor>
      <arglist>(Event &amp;event)</arglist>
    </member>
    <member kind="function">
      <type>const std::string &amp;</type>
      <name>GetName</name>
      <anchorfile>class_real_engine_1_1_layer.html</anchorfile>
      <anchor>a25b0ce3268233151a9299a20f7157932</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::string</type>
      <name>m_DebugName</name>
      <anchorfile>class_real_engine_1_1_layer.html</anchorfile>
      <anchor>afdd82bbf56f14c50f2127031e3edf4b2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RealEngine::LayerStack</name>
    <filename>class_real_engine_1_1_layer_stack.html</filename>
    <member kind="function">
      <type></type>
      <name>LayerStack</name>
      <anchorfile>class_real_engine_1_1_layer_stack.html</anchorfile>
      <anchor>ab80bff69d71517ccd0fee3b3c1cddfda</anchor>
      <arglist>()=default</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~LayerStack</name>
      <anchorfile>class_real_engine_1_1_layer_stack.html</anchorfile>
      <anchor>aa95eda11fca20774a204db077380e5ca</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Clear</name>
      <anchorfile>class_real_engine_1_1_layer_stack.html</anchorfile>
      <anchor>a0592be3a42c48c6dd42c1bba702737a3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PushLayer</name>
      <anchorfile>class_real_engine_1_1_layer_stack.html</anchorfile>
      <anchor>a3c3b1da0b88dcc77edc682d27fd44f27</anchor>
      <arglist>(Layer *layer)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PopLayer</name>
      <anchorfile>class_real_engine_1_1_layer_stack.html</anchorfile>
      <anchor>a6b5d97f37ee5fa2779c7d9799c22d04e</anchor>
      <arglist>(Layer *layer)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PushOverlay</name>
      <anchorfile>class_real_engine_1_1_layer_stack.html</anchorfile>
      <anchor>abcff305ea18f6a652bcbb8e5f5cf0b2b</anchor>
      <arglist>(Layer *overlay)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PopOverlay</name>
      <anchorfile>class_real_engine_1_1_layer_stack.html</anchorfile>
      <anchor>a02c4655325f937c6fb825a0cc35f5aff</anchor>
      <arglist>(Layer *overlay)</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; Layer * &gt;::iterator</type>
      <name>begin</name>
      <anchorfile>class_real_engine_1_1_layer_stack.html</anchorfile>
      <anchor>ac213e967b9b81205fbeebe020de66f9b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; Layer * &gt;::iterator</type>
      <name>end</name>
      <anchorfile>class_real_engine_1_1_layer_stack.html</anchorfile>
      <anchor>a50325d011e940e50bb28e3755ec4f2e9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>std::vector&lt; Layer * &gt;</type>
      <name>m_Layers</name>
      <anchorfile>class_real_engine_1_1_layer_stack.html</anchorfile>
      <anchor>ad33f57f8e56ef7f76a227915c63a7c4c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>unsigned int</type>
      <name>m_LayerInsertIndex</name>
      <anchorfile>class_real_engine_1_1_layer_stack.html</anchorfile>
      <anchor>af421ad5f62317174c43a46845c4c069c</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RealEngine::Log</name>
    <filename>class_real_engine_1_1_log.html</filename>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>Init</name>
      <anchorfile>class_real_engine_1_1_log.html</anchorfile>
      <anchor>ad4be3aed90a5671eac5f6a3d113409c3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>Flush</name>
      <anchorfile>class_real_engine_1_1_log.html</anchorfile>
      <anchor>a32473331e625e4ecb5882ce18cdf740a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static quill::Logger *</type>
      <name>GetCoreLogger</name>
      <anchorfile>class_real_engine_1_1_log.html</anchorfile>
      <anchor>a7b72178cfd40bf4357fbd4a906c27f23</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static quill::Logger *</type>
      <name>GetClientLogger</name>
      <anchorfile>class_real_engine_1_1_log.html</anchorfile>
      <anchor>a3c1f06fb039ed49a1831687a7eb6c101</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="private" static="yes">
      <type>static quill::Logger *</type>
      <name>s_CoreLogger</name>
      <anchorfile>class_real_engine_1_1_log.html</anchorfile>
      <anchor>a08ba3b8b37753f8f767c7bfa483e19fa</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private" static="yes">
      <type>static quill::Logger *</type>
      <name>s_ClientLogger</name>
      <anchorfile>class_real_engine_1_1_log.html</anchorfile>
      <anchor>a2bd1136ca0bfca028834304fe965e50d</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RealEngine::MouseButtonPressedEvent</name>
    <filename>class_real_engine_1_1_mouse_button_pressed_event.html</filename>
    <base>RealEngine::Event</base>
    <member kind="function">
      <type></type>
      <name>MouseButtonPressedEvent</name>
      <anchorfile>class_real_engine_1_1_mouse_button_pressed_event.html</anchorfile>
      <anchor>ada8d23896dc89544b0494f1c417c39ed</anchor>
      <arglist>(MouseCode button)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetButton</name>
      <anchorfile>class_real_engine_1_1_mouse_button_pressed_event.html</anchorfile>
      <anchor>ad3a483d7e2962b10ffd16d662303c288</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual std::string</type>
      <name>ToString</name>
      <anchorfile>class_real_engine_1_1_mouse_button_pressed_event.html</anchorfile>
      <anchor>a28a9f55847fc92c94ebd1c0226c5c1b7</anchor>
      <arglist>() const override</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>MouseCode</type>
      <name>m_Button</name>
      <anchorfile>class_real_engine_1_1_mouse_button_pressed_event.html</anchorfile>
      <anchor>a40737f3b7f36a739cdd6d5d426b8aef0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RealEngine::MouseButtonReleasedEvent</name>
    <filename>class_real_engine_1_1_mouse_button_released_event.html</filename>
    <base>RealEngine::Event</base>
    <member kind="function">
      <type></type>
      <name>MouseButtonReleasedEvent</name>
      <anchorfile>class_real_engine_1_1_mouse_button_released_event.html</anchorfile>
      <anchor>aef69cf47773cb64c60e8225a8bda02b5</anchor>
      <arglist>(MouseCode button)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetButton</name>
      <anchorfile>class_real_engine_1_1_mouse_button_released_event.html</anchorfile>
      <anchor>a4fdd97fe8a4d07cabc873e46414d490c</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual std::string</type>
      <name>ToString</name>
      <anchorfile>class_real_engine_1_1_mouse_button_released_event.html</anchorfile>
      <anchor>abcef8b59a1ecac5de9553407a0ed6456</anchor>
      <arglist>() const override</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>MouseCode</type>
      <name>m_Button</name>
      <anchorfile>class_real_engine_1_1_mouse_button_released_event.html</anchorfile>
      <anchor>a97ee8214e64b362585ecc01ae550ee98</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RealEngine::MouseMovedEvent</name>
    <filename>class_real_engine_1_1_mouse_moved_event.html</filename>
    <base>RealEngine::Event</base>
    <member kind="function">
      <type></type>
      <name>MouseMovedEvent</name>
      <anchorfile>class_real_engine_1_1_mouse_moved_event.html</anchorfile>
      <anchor>a90cfaa3a51652178d6d4c66e59f75633</anchor>
      <arglist>(float x, float y)</arglist>
    </member>
    <member kind="function">
      <type>float</type>
      <name>GetX</name>
      <anchorfile>class_real_engine_1_1_mouse_moved_event.html</anchorfile>
      <anchor>a0e08dd3f885b346383a26515f88ee401</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>float</type>
      <name>GetY</name>
      <anchorfile>class_real_engine_1_1_mouse_moved_event.html</anchorfile>
      <anchor>ac8b8bac147a1cf9050c6ada6d9ad476f</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual std::string</type>
      <name>ToString</name>
      <anchorfile>class_real_engine_1_1_mouse_moved_event.html</anchorfile>
      <anchor>a0f0b5371fbb3154196923b9c595c901e</anchor>
      <arglist>() const override</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>float</type>
      <name>m_X</name>
      <anchorfile>class_real_engine_1_1_mouse_moved_event.html</anchorfile>
      <anchor>a11f1e5f612de66e2ff9492f097a88035</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>float</type>
      <name>m_Y</name>
      <anchorfile>class_real_engine_1_1_mouse_moved_event.html</anchorfile>
      <anchor>a48992819ad02ec06bc7f0227b6c666bf</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RealEngine::MouseScrolledEvent</name>
    <filename>class_real_engine_1_1_mouse_scrolled_event.html</filename>
    <base>RealEngine::Event</base>
    <member kind="function">
      <type></type>
      <name>MouseScrolledEvent</name>
      <anchorfile>class_real_engine_1_1_mouse_scrolled_event.html</anchorfile>
      <anchor>a764b86a4874a5d593e3f3c8216c6b27a</anchor>
      <arglist>(float xOffset, float yOffset)</arglist>
    </member>
    <member kind="function">
      <type>float</type>
      <name>GetXOffset</name>
      <anchorfile>class_real_engine_1_1_mouse_scrolled_event.html</anchorfile>
      <anchor>ad8f280ba81c09c92a6f11b5f0ed75896</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>float</type>
      <name>GetYOffset</name>
      <anchorfile>class_real_engine_1_1_mouse_scrolled_event.html</anchorfile>
      <anchor>a3b360bd2303a1a727986061a0d3a7e8e</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual std::string</type>
      <name>ToString</name>
      <anchorfile>class_real_engine_1_1_mouse_scrolled_event.html</anchorfile>
      <anchor>a4edbe2ac3bb6a3d949c9abb7acc37764</anchor>
      <arglist>() const override</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>float</type>
      <name>m_XOffset</name>
      <anchorfile>class_real_engine_1_1_mouse_scrolled_event.html</anchorfile>
      <anchor>a0b0b1d5a3521059335ad1d944bdd30b0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>float</type>
      <name>m_YOffset</name>
      <anchorfile>class_real_engine_1_1_mouse_scrolled_event.html</anchorfile>
      <anchor>af3f94bcf1a51b104ccab9a3aaa99988c</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RealEngine::PathHash</name>
    <filename>class_real_engine_1_1_path_hash.html</filename>
    <member kind="function">
      <type></type>
      <name>PathHash</name>
      <anchorfile>class_real_engine_1_1_path_hash.html</anchorfile>
      <anchor>a80fcd2468ecb560c00413c5cf87d46f5</anchor>
      <arglist>(const std::filesystem::path &amp;path)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>PathHash</name>
      <anchorfile>class_real_engine_1_1_path_hash.html</anchorfile>
      <anchor>adff1c1fcbd7df95609414ac7a9cae84a</anchor>
      <arglist>(const char *string)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>operator uint32_t</name>
      <anchorfile>class_real_engine_1_1_path_hash.html</anchorfile>
      <anchor>a63a51134025a75d68e7da23ee4dd26b6</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator==</name>
      <anchorfile>class_real_engine_1_1_path_hash.html</anchorfile>
      <anchor>a57828c92292cf5c4ea57685ec7faf06c</anchor>
      <arglist>(const PathHash &amp;other) const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator!=</name>
      <anchorfile>class_real_engine_1_1_path_hash.html</anchorfile>
      <anchor>a55a17f02d2d776427d5b49bafe3bae7b</anchor>
      <arglist>(const PathHash &amp;other) const</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>uint32_t</type>
      <name>m_Hash</name>
      <anchorfile>class_real_engine_1_1_path_hash.html</anchorfile>
      <anchor>a9548b86cea23d4befe496139a6a90898</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RealEngine::RenderCommands</name>
    <filename>class_real_engine_1_1_render_commands.html</filename>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>Init</name>
      <anchorfile>class_real_engine_1_1_render_commands.html</anchorfile>
      <anchor>a110ec20610ae392387f579d4b9f381f7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>Clear</name>
      <anchorfile>class_real_engine_1_1_render_commands.html</anchorfile>
      <anchor>a02f72636d78454ca947ea868d4e1cc4c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>SetClearColor</name>
      <anchorfile>class_real_engine_1_1_render_commands.html</anchorfile>
      <anchor>a1081a4613214be684402dc78364e04ad</anchor>
      <arglist>(const glm::vec4 &amp;color)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>SetViewport</name>
      <anchorfile>class_real_engine_1_1_render_commands.html</anchorfile>
      <anchor>a8b815ddba293085610f5f82349322d8c</anchor>
      <arglist>(uint32_t x, uint32_t y, uint32_t width, uint32_t height)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>SetWireframe</name>
      <anchorfile>class_real_engine_1_1_render_commands.html</anchorfile>
      <anchor>a19456f9ba45be98a25d8960ff34693bf</anchor>
      <arglist>(bool enabled)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>SetFaceCulling</name>
      <anchorfile>class_real_engine_1_1_render_commands.html</anchorfile>
      <anchor>a7cfc1c04c0fadaaf2f590792cf817ec7</anchor>
      <arglist>(bool enabled)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>DrawIndexed</name>
      <anchorfile>class_real_engine_1_1_render_commands.html</anchorfile>
      <anchor>a6faf721f8991a46212e8813eec7b0357</anchor>
      <arglist>(Ref&lt; VertexArray &gt; vertexArray, uint32_t indexCount=0)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>DrawArrays</name>
      <anchorfile>class_real_engine_1_1_render_commands.html</anchorfile>
      <anchor>ac04a3579fbc6520477dff6cafb7ab9e4</anchor>
      <arglist>(Ref&lt; VertexArray &gt; vertexArray, uint32_t count)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>DrawMutliIndexedIndirect</name>
      <anchorfile>class_real_engine_1_1_render_commands.html</anchorfile>
      <anchor>a291f505079054e6daa09ebf1d97e5a7f</anchor>
      <arglist>(Ref&lt; VertexArray &gt; vertexArray, uint32_t commandCount)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RealEngine::Renderer</name>
    <filename>class_real_engine_1_1_renderer.html</filename>
    <member kind="function">
      <type>void</type>
      <name>Render</name>
      <anchorfile>class_real_engine_1_1_renderer.html</anchorfile>
      <anchor>aed5438e9ac167159bbc76ccf014607a3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>Init</name>
      <anchorfile>class_real_engine_1_1_renderer.html</anchorfile>
      <anchor>a8d4e5dfeaabc960397fd035ef123449d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>Shutdown</name>
      <anchorfile>class_real_engine_1_1_renderer.html</anchorfile>
      <anchor>a9c986a520ffb8762d16b486f54e62aa2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>DrawQuad</name>
      <anchorfile>class_real_engine_1_1_renderer.html</anchorfile>
      <anchor>a4253f054ef443eda104d0bdc2388bb8b</anchor>
      <arglist>(const glm::vec3 &amp;position)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Renderer *</type>
      <name>Get</name>
      <anchorfile>class_real_engine_1_1_renderer.html</anchorfile>
      <anchor>a74b49ac55e52bb1ff45d3eec6d02bca2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="private" static="yes">
      <type>static Renderer *</type>
      <name>m_Renderer</name>
      <anchorfile>class_real_engine_1_1_renderer.html</anchorfile>
      <anchor>aabc24d72ed1d945ac8bcb2409b8b40bf</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private" static="yes">
      <type>static Ref&lt; Texture2D &gt;</type>
      <name>m_Texture</name>
      <anchorfile>class_real_engine_1_1_renderer.html</anchorfile>
      <anchor>a9dc1b6ebd48945cabd7546405f11b7d0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RealEngine::Shader</name>
    <filename>class_real_engine_1_1_shader.html</filename>
    <member kind="function">
      <type></type>
      <name>Shader</name>
      <anchorfile>class_real_engine_1_1_shader.html</anchorfile>
      <anchor>a51d15140f47f7edb7198bff66aaae4b7</anchor>
      <arglist>(const std::filesystem::path &amp;file)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Shader</name>
      <anchorfile>class_real_engine_1_1_shader.html</anchorfile>
      <anchor>a56b949b38253a87d46fa4cc4e422fd1e</anchor>
      <arglist>(const char *vertexShaderSource, const char *fragmentShaderSource)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Shader</name>
      <anchorfile>class_real_engine_1_1_shader.html</anchorfile>
      <anchor>a25426c360b27461e058540450b711165</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Bind</name>
      <anchorfile>class_real_engine_1_1_shader.html</anchorfile>
      <anchor>af86fcc78a58f87abe2e5f6c219e8e936</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetUniformint</name>
      <anchorfile>class_real_engine_1_1_shader.html</anchorfile>
      <anchor>a2a472a053058d19d2b811cbd4f0c74e9</anchor>
      <arglist>(const std::string &amp;name, int value)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetUniformFloat</name>
      <anchorfile>class_real_engine_1_1_shader.html</anchorfile>
      <anchor>a530ed551b16052431023775ea884278f</anchor>
      <arglist>(const std::string &amp;name, float value)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetUniformVec2</name>
      <anchorfile>class_real_engine_1_1_shader.html</anchorfile>
      <anchor>a00f401073d9a7d1860ef7bba6932ddf1</anchor>
      <arglist>(const std::string &amp;name, const glm::vec2 &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetUniformVec3</name>
      <anchorfile>class_real_engine_1_1_shader.html</anchorfile>
      <anchor>a0d36f37332874b10f4e7aa61d7e37ae9</anchor>
      <arglist>(const std::string &amp;name, const glm::vec3 &amp;value)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetUniformVec4</name>
      <anchorfile>class_real_engine_1_1_shader.html</anchorfile>
      <anchor>a176af368d45dae27e83aa1c24888eca9</anchor>
      <arglist>(const std::string &amp;name, const glm::vec4 &amp;value)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Ref&lt; Shader &gt;</type>
      <name>Create</name>
      <anchorfile>class_real_engine_1_1_shader.html</anchorfile>
      <anchor>aec122bd63b07a543969602985ed9bca5</anchor>
      <arglist>(const std::filesystem::path &amp;file)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Ref&lt; Shader &gt;</type>
      <name>Create</name>
      <anchorfile>class_real_engine_1_1_shader.html</anchorfile>
      <anchor>a0a9781e1a4cfe1edaf5280bff0e8dbd9</anchor>
      <arglist>(const char *vertexShaderSource, const char *fragmentShaderSource)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>CompileShader</name>
      <anchorfile>class_real_engine_1_1_shader.html</anchorfile>
      <anchor>a352f3a640e9f3613bcf616eccda62d6a</anchor>
      <arglist>(const std::vector&lt; ShaderProcessing &gt; &amp;shaderProcessing)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>ParseFile</name>
      <anchorfile>class_real_engine_1_1_shader.html</anchorfile>
      <anchor>ae1137f859d2ca0455e376fda6f797353</anchor>
      <arglist>(const std::filesystem::path &amp;file)</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>uint32_t</type>
      <name>m_ShaderID</name>
      <anchorfile>class_real_engine_1_1_shader.html</anchorfile>
      <anchor>af96ba96ac909e8de208d6448fa6784de</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>RealEngine::ShaderProcessing</name>
    <filename>struct_real_engine_1_1_shader_processing.html</filename>
    <member kind="variable">
      <type>std::string</type>
      <name>ShaderCode</name>
      <anchorfile>struct_real_engine_1_1_shader_processing.html</anchorfile>
      <anchor>a415104d692f481f89ba75f8b02ec2d74</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const ShaderTypes</type>
      <name>ShaderType</name>
      <anchorfile>struct_real_engine_1_1_shader_processing.html</anchorfile>
      <anchor>af8ad7bd8f3f64655ff4ebb84e89ca9ad</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RealEngine::ShaderStorageBuffer</name>
    <filename>class_real_engine_1_1_shader_storage_buffer.html</filename>
    <base>RealEngine::Utils::Buffer</base>
    <member kind="function">
      <type></type>
      <name>ShaderStorageBuffer</name>
      <anchorfile>class_real_engine_1_1_shader_storage_buffer.html</anchorfile>
      <anchor>a2707de8908006301c64bb5d8fa2f2a67</anchor>
      <arglist>(uint32_t size, uint32_t binding)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ShaderStorageBuffer</name>
      <anchorfile>class_real_engine_1_1_shader_storage_buffer.html</anchorfile>
      <anchor>af65561efa2bea65d940294f8714328d2</anchor>
      <arglist>(const void *data, uint32_t size, uint32_t binding)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetBinding</name>
      <anchorfile>class_real_engine_1_1_shader_storage_buffer.html</anchorfile>
      <anchor>a76d393ee85d9dc1f62de806fbc1fa8e6</anchor>
      <arglist>(uint32_t binding)</arglist>
    </member>
    <member kind="function">
      <type>uint32_t</type>
      <name>GetBinding</name>
      <anchorfile>class_real_engine_1_1_shader_storage_buffer.html</anchorfile>
      <anchor>a701d3cd3a40e5210e78395ad0e5ec299</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Ref&lt; ShaderStorageBuffer &gt;</type>
      <name>Create</name>
      <anchorfile>class_real_engine_1_1_shader_storage_buffer.html</anchorfile>
      <anchor>a8f7ad7d4040f8da024666131ca84401b</anchor>
      <arglist>(uint32_t size, uint32_t binding)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Ref&lt; ShaderStorageBuffer &gt;</type>
      <name>Create</name>
      <anchorfile>class_real_engine_1_1_shader_storage_buffer.html</anchorfile>
      <anchor>ae01433d9f73dec1e5cebe59ee5fa2911</anchor>
      <arglist>(const void *data, uint32_t size, uint32_t binding)</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>uint32_t</type>
      <name>m_Binding</name>
      <anchorfile>class_real_engine_1_1_shader_storage_buffer.html</anchorfile>
      <anchor>af7423463548c5df4fa790192067d5fd0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RealEngine::StringHash</name>
    <filename>class_real_engine_1_1_string_hash.html</filename>
    <member kind="function">
      <type></type>
      <name>StringHash</name>
      <anchorfile>class_real_engine_1_1_string_hash.html</anchorfile>
      <anchor>aa64d49e056c8e526542b923e2e7fc3e7</anchor>
      <arglist>(const std::string &amp;string)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>StringHash</name>
      <anchorfile>class_real_engine_1_1_string_hash.html</anchorfile>
      <anchor>a15288369f0dfd5d48f1383099fb87506</anchor>
      <arglist>(const char *string)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>operator uint32_t</name>
      <anchorfile>class_real_engine_1_1_string_hash.html</anchorfile>
      <anchor>a473fa81b1efa6bc275ab38c3b04f8fd7</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator==</name>
      <anchorfile>class_real_engine_1_1_string_hash.html</anchorfile>
      <anchor>a91ac899554517cbf0c2e3dd2739b5521</anchor>
      <arglist>(const StringHash &amp;other) const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator!=</name>
      <anchorfile>class_real_engine_1_1_string_hash.html</anchorfile>
      <anchor>afd55d63697e91441803eb1c1971522e9</anchor>
      <arglist>(const StringHash &amp;other) const</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>uint32_t</type>
      <name>m_Hash</name>
      <anchorfile>class_real_engine_1_1_string_hash.html</anchorfile>
      <anchor>a2901bd2b4dfed538efc53a3e545a3e72</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RealEngine::Texture2D</name>
    <filename>class_real_engine_1_1_texture2_d.html</filename>
    <member kind="function">
      <type></type>
      <name>Texture2D</name>
      <anchorfile>class_real_engine_1_1_texture2_d.html</anchorfile>
      <anchor>ad402c5a2525f70f152136853509dba7a</anchor>
      <arglist>(const std::filesystem::path &amp;path)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Texture2D</name>
      <anchorfile>class_real_engine_1_1_texture2_d.html</anchorfile>
      <anchor>ab55769770e6b3deb041df06850b9fefa</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Bind</name>
      <anchorfile>class_real_engine_1_1_texture2_d.html</anchorfile>
      <anchor>a0d27b0e7d36573a104212d81b0934a9d</anchor>
      <arglist>(uint32_t slot=0) const</arglist>
    </member>
    <member kind="function">
      <type>uint32_t</type>
      <name>GetWidth</name>
      <anchorfile>class_real_engine_1_1_texture2_d.html</anchorfile>
      <anchor>a096c00463d7cf6fae91d67dfaa3bff0c</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>uint32_t</type>
      <name>GetHeight</name>
      <anchorfile>class_real_engine_1_1_texture2_d.html</anchorfile>
      <anchor>af0633ad57297ac1bbd16a217259e4526</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Ref&lt; Texture2D &gt;</type>
      <name>Create</name>
      <anchorfile>class_real_engine_1_1_texture2_d.html</anchorfile>
      <anchor>a23dcd9b0aa76b224a2ce369fa57fa70f</anchor>
      <arglist>(const std::filesystem::path &amp;path)</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>uint32_t</type>
      <name>m_Width</name>
      <anchorfile>class_real_engine_1_1_texture2_d.html</anchorfile>
      <anchor>a1290e8729e8fcad612ff28709c1ba6f1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>uint32_t</type>
      <name>m_Height</name>
      <anchorfile>class_real_engine_1_1_texture2_d.html</anchorfile>
      <anchor>afe8d9eba36896c4b2fc8f0efc0248f88</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>uint32_t</type>
      <name>m_RendererID</name>
      <anchorfile>class_real_engine_1_1_texture2_d.html</anchorfile>
      <anchor>a92f169d29cf3141fc717ebac41e42e6d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>PathHash</type>
      <name>m_FilePath</name>
      <anchorfile>class_real_engine_1_1_texture2_d.html</anchorfile>
      <anchor>a5ff8c4e46969394d74526c847285875e</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RealEngine::Texture2DArray</name>
    <filename>class_real_engine_1_1_texture2_d_array.html</filename>
    <class kind="struct">RealEngine::Texture2DArray::TextureData</class>
    <member kind="function">
      <type></type>
      <name>Texture2DArray</name>
      <anchorfile>class_real_engine_1_1_texture2_d_array.html</anchorfile>
      <anchor>a5ce73f6b959d42c7f72a393be0690901</anchor>
      <arglist>(const Texture2DArrayCreateInfo &amp;info, const void **data=nullptr)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Texture2DArray</name>
      <anchorfile>class_real_engine_1_1_texture2_d_array.html</anchorfile>
      <anchor>a773f97801c61a52f0e2084030e5a84e2</anchor>
      <arglist>(const std::initializer_list&lt; std::filesystem::path &gt; paths, uint32_t mipLevels=1)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Texture2DArray</name>
      <anchorfile>class_real_engine_1_1_texture2_d_array.html</anchorfile>
      <anchor>a2d641048e8e8357a53fe91e27ea95935</anchor>
      <arglist>(const std::vector&lt; std::filesystem::path &gt; &amp;paths, uint32_t mipLevels=1)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Texture2DArray</name>
      <anchorfile>class_real_engine_1_1_texture2_d_array.html</anchorfile>
      <anchor>aab1aeca1345c9d889da973692aa11bd5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Bind</name>
      <anchorfile>class_real_engine_1_1_texture2_d_array.html</anchorfile>
      <anchor>a0b2d4204172a061b4ece7c98a5a949a9</anchor>
      <arglist>(uint32_t slot=0) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetSubTextureData</name>
      <anchorfile>class_real_engine_1_1_texture2_d_array.html</anchorfile>
      <anchor>acd040744848c9a1903e15740cf8f4730</anchor>
      <arglist>(const void *data, uint32_t zOffset)</arglist>
    </member>
    <member kind="function">
      <type>uint32_t</type>
      <name>GetWidth</name>
      <anchorfile>class_real_engine_1_1_texture2_d_array.html</anchorfile>
      <anchor>abec6e97bcb6863c65cf100269783fe65</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>uint32_t</type>
      <name>GetHeight</name>
      <anchorfile>class_real_engine_1_1_texture2_d_array.html</anchorfile>
      <anchor>a37ce41aa86b16de70b57f6abb6e7ed00</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>uint32_t</type>
      <name>GetLength</name>
      <anchorfile>class_real_engine_1_1_texture2_d_array.html</anchorfile>
      <anchor>a661b458849aeb6acdea1d0a4590b7c4c</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Ref&lt; Texture2DArray &gt;</type>
      <name>Create</name>
      <anchorfile>class_real_engine_1_1_texture2_d_array.html</anchorfile>
      <anchor>a5df39f68aaafdbdf9bb3661e9cd26d0a</anchor>
      <arglist>(const Texture2DArrayCreateInfo &amp;info, const void **data=nullptr)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Ref&lt; Texture2DArray &gt;</type>
      <name>Create</name>
      <anchorfile>class_real_engine_1_1_texture2_d_array.html</anchorfile>
      <anchor>ab5e3963d253ed83c1a353cba7080e054</anchor>
      <arglist>(const std::initializer_list&lt; std::filesystem::path &gt; paths, uint32_t mipLevels=1)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Ref&lt; Texture2DArray &gt;</type>
      <name>Create</name>
      <anchorfile>class_real_engine_1_1_texture2_d_array.html</anchorfile>
      <anchor>af13bbc70f5aff94dd99694c728741fa7</anchor>
      <arglist>(const std::vector&lt; std::filesystem::path &gt; &amp;paths, uint32_t mipLevels=1)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>LoadTextures</name>
      <anchorfile>class_real_engine_1_1_texture2_d_array.html</anchorfile>
      <anchor>a30512448c503ad396d982799a9d5ce36</anchor>
      <arglist>(It begin, uint32_t numTextures, uint32_t mipLevels)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>CreateTextureArray</name>
      <anchorfile>class_real_engine_1_1_texture2_d_array.html</anchorfile>
      <anchor>ab8ff23aa8f421165ea90a5bfe13b5057</anchor>
      <arglist>(const void **data, TextureDataType internalFormat, TextureFormat dataFormat, uint32_t numTextures, uint32_t mipLevels)</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>uint32_t</type>
      <name>m_Width</name>
      <anchorfile>class_real_engine_1_1_texture2_d_array.html</anchorfile>
      <anchor>a0f48cb045e75a23d3cff874de1d77049</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>uint32_t</type>
      <name>m_Height</name>
      <anchorfile>class_real_engine_1_1_texture2_d_array.html</anchorfile>
      <anchor>a395fa8087fd8e0fd1c199e434b78be2c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>uint32_t</type>
      <name>m_Length</name>
      <anchorfile>class_real_engine_1_1_texture2_d_array.html</anchorfile>
      <anchor>ab5974b48c4faccbd195511bb1a8cac52</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>TextureDataType</type>
      <name>m_InternalFormat</name>
      <anchorfile>class_real_engine_1_1_texture2_d_array.html</anchorfile>
      <anchor>a4fd1dd3f8588ed9286b78b4477f5e2f6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>TextureFormat</type>
      <name>m_DataFormat</name>
      <anchorfile>class_real_engine_1_1_texture2_d_array.html</anchorfile>
      <anchor>a3224e73ce52e2c79c79f6eeb44126b4c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>uint32_t</type>
      <name>m_RendererID</name>
      <anchorfile>class_real_engine_1_1_texture2_d_array.html</anchorfile>
      <anchor>ac4ab9a4082ca65af1bed370c34f8ee94</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>RealEngine::Texture2DArrayCreateInfo</name>
    <filename>struct_real_engine_1_1_texture2_d_array_create_info.html</filename>
    <member kind="variable">
      <type>uint32_t</type>
      <name>Width</name>
      <anchorfile>struct_real_engine_1_1_texture2_d_array_create_info.html</anchorfile>
      <anchor>ac413034ab70800a2daf53cc80acf34dd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>Height</name>
      <anchorfile>struct_real_engine_1_1_texture2_d_array_create_info.html</anchorfile>
      <anchor>a88d4994b109c22b916d1ebfc48e71d58</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>NumTextures</name>
      <anchorfile>struct_real_engine_1_1_texture2_d_array_create_info.html</anchorfile>
      <anchor>a470da0f700aebb1fcfa5196521137ff9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>TextureDataType</type>
      <name>InternalFormat</name>
      <anchorfile>struct_real_engine_1_1_texture2_d_array_create_info.html</anchorfile>
      <anchor>ac1729cb254deb1572c4e41f722202c2f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>TextureFormat</type>
      <name>DataFormat</name>
      <anchorfile>struct_real_engine_1_1_texture2_d_array_create_info.html</anchorfile>
      <anchor>a2a561a25ddb7ad5acbe84aff66b906b9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>MipLevels</name>
      <anchorfile>struct_real_engine_1_1_texture2_d_array_create_info.html</anchorfile>
      <anchor>ab9f89bacd7160e1a944ebdbc70ff2de6</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>RealEngine::Texture2DArray::TextureData</name>
    <filename>struct_real_engine_1_1_texture2_d_array_1_1_texture_data.html</filename>
    <member kind="variable">
      <type>int</type>
      <name>Width</name>
      <anchorfile>struct_real_engine_1_1_texture2_d_array_1_1_texture_data.html</anchorfile>
      <anchor>a40d87686709218330824de986d56f5d0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>Height</name>
      <anchorfile>struct_real_engine_1_1_texture2_d_array_1_1_texture_data.html</anchorfile>
      <anchor>a4ad9630e8d0d85dc2338604d0a6ec13e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>Channels</name>
      <anchorfile>struct_real_engine_1_1_texture2_d_array_1_1_texture_data.html</anchorfile>
      <anchor>ae7e15df17bb0b6aa6331e72f28bd8e8b</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RealEngine::TextureManager</name>
    <filename>class_real_engine_1_1_texture_manager.html</filename>
    <base>RealEngine::GeneralManager&lt; Texture2D &gt;</base>
    <member kind="function" static="yes">
      <type>static Ref&lt; Texture2D &gt;</type>
      <name>LoadTexture</name>
      <anchorfile>class_real_engine_1_1_texture_manager.html</anchorfile>
      <anchor>a092a3839d9dfb8c631de668a13c9994a</anchor>
      <arglist>(const std::filesystem::path &amp;path)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RealEngine::UniformBuffer</name>
    <filename>class_real_engine_1_1_uniform_buffer.html</filename>
    <base>RealEngine::Utils::Buffer</base>
    <member kind="function">
      <type></type>
      <name>UniformBuffer</name>
      <anchorfile>class_real_engine_1_1_uniform_buffer.html</anchorfile>
      <anchor>a9406ea387f63cbb7f2c85852dae4c1d2</anchor>
      <arglist>(uint32_t size, uint32_t binding)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>UniformBuffer</name>
      <anchorfile>class_real_engine_1_1_uniform_buffer.html</anchorfile>
      <anchor>a679c884794773bd72edaa03dd4c8e913</anchor>
      <arglist>(const void *data, uint32_t size, uint32_t binding)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetBinding</name>
      <anchorfile>class_real_engine_1_1_uniform_buffer.html</anchorfile>
      <anchor>aa558afc0eb4ecf893a0c6d5001b51a3d</anchor>
      <arglist>(uint32_t binding)</arglist>
    </member>
    <member kind="function">
      <type>uint32_t</type>
      <name>GetBinding</name>
      <anchorfile>class_real_engine_1_1_uniform_buffer.html</anchorfile>
      <anchor>a6aa2fea1c07c2cac0ff5f2c722a03e32</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Ref&lt; UniformBuffer &gt;</type>
      <name>Create</name>
      <anchorfile>class_real_engine_1_1_uniform_buffer.html</anchorfile>
      <anchor>a3a6a17455600423957660311a552fe14</anchor>
      <arglist>(uint32_t size, uint32_t binding)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Ref&lt; UniformBuffer &gt;</type>
      <name>Create</name>
      <anchorfile>class_real_engine_1_1_uniform_buffer.html</anchorfile>
      <anchor>ac215998038c40cc44cec9d503f50e57a</anchor>
      <arglist>(const void *data, uint32_t size, uint32_t binding)</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>uint32_t</type>
      <name>m_Binding</name>
      <anchorfile>class_real_engine_1_1_uniform_buffer.html</anchorfile>
      <anchor>aff597a0fe604b5c6de1002267a5f9488</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RealEngine::UUID</name>
    <filename>class_real_engine_1_1_u_u_i_d.html</filename>
    <member kind="function">
      <type></type>
      <name>UUID</name>
      <anchorfile>class_real_engine_1_1_u_u_i_d.html</anchorfile>
      <anchor>afaa2bff5f29258aa741e25c1740623b3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>operator uint64_t</name>
      <anchorfile>class_real_engine_1_1_u_u_i_d.html</anchorfile>
      <anchor>a97be344692f47aafd9268a9f2386e19f</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator==</name>
      <anchorfile>class_real_engine_1_1_u_u_i_d.html</anchorfile>
      <anchor>a8500b615ad27337c698d4d127cf37677</anchor>
      <arglist>(const UUID &amp;other) const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator!=</name>
      <anchorfile>class_real_engine_1_1_u_u_i_d.html</anchorfile>
      <anchor>a49834c13d9b1387c132b01ba2e218652</anchor>
      <arglist>(const UUID &amp;other) const</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>uint64_t</type>
      <name>m_UUID</name>
      <anchorfile>class_real_engine_1_1_u_u_i_d.html</anchorfile>
      <anchor>a8eb1d6593a371c95af330cc049909630</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RealEngine::VertexArray</name>
    <filename>class_real_engine_1_1_vertex_array.html</filename>
    <member kind="function">
      <type></type>
      <name>VertexArray</name>
      <anchorfile>class_real_engine_1_1_vertex_array.html</anchorfile>
      <anchor>a44366f0a29eb8d351e9aee1763b4a2aa</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~VertexArray</name>
      <anchorfile>class_real_engine_1_1_vertex_array.html</anchorfile>
      <anchor>a87b7b7b9e61867c79d07d729f5ef9397</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Bind</name>
      <anchorfile>class_real_engine_1_1_vertex_array.html</anchorfile>
      <anchor>a3a84d2b9edfefbe3df4a6cc8aaf5af91</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Unbind</name>
      <anchorfile>class_real_engine_1_1_vertex_array.html</anchorfile>
      <anchor>a7e2f93f73bbf862c4457b506cc337a99</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetVertexBuffer</name>
      <anchorfile>class_real_engine_1_1_vertex_array.html</anchorfile>
      <anchor>afbc586e0cc957de0a24aff381e1c3e85</anchor>
      <arglist>(Ref&lt; VertexBuffer &gt; vertexBuffer)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetVertexBuffers</name>
      <anchorfile>class_real_engine_1_1_vertex_array.html</anchorfile>
      <anchor>ab1801257e86d3b2965c1510399c6e531</anchor>
      <arglist>(std::vector&lt; Ref&lt; VertexBuffer &gt; &gt; vertexBuffers)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetIndexBuffer</name>
      <anchorfile>class_real_engine_1_1_vertex_array.html</anchorfile>
      <anchor>a64c050cd8a4becbdd2ba06621a7959dd</anchor>
      <arglist>(Ref&lt; IndexBuffer &gt; indexBuffer)</arglist>
    </member>
    <member kind="function">
      <type>const Ref&lt; VertexBuffer &gt;</type>
      <name>GetVertexBuffer</name>
      <anchorfile>class_real_engine_1_1_vertex_array.html</anchorfile>
      <anchor>a69f54d544d3ded235ba71a63b1d65847</anchor>
      <arglist>(uint8_t index=0) const</arglist>
    </member>
    <member kind="function">
      <type>const Ref&lt; IndexBuffer &gt;</type>
      <name>GetIndexBuffer</name>
      <anchorfile>class_real_engine_1_1_vertex_array.html</anchorfile>
      <anchor>a43ded8ebbd669f7f9dce0899238d7026</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Ref&lt; VertexArray &gt;</type>
      <name>Create</name>
      <anchorfile>class_real_engine_1_1_vertex_array.html</anchorfile>
      <anchor>abbe3d9c1eb168cfb5f206ab76951e5aa</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>uint32_t</type>
      <name>m_RendererID</name>
      <anchorfile>class_real_engine_1_1_vertex_array.html</anchorfile>
      <anchor>af62f46a6894ea0dd9c9e7348def6fe5a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>std::vector&lt; Ref&lt; VertexBuffer &gt; &gt;</type>
      <name>m_VertexBuffer</name>
      <anchorfile>class_real_engine_1_1_vertex_array.html</anchorfile>
      <anchor>a051ace97aaeeceb181a008b2320a3b8f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>Ref&lt; IndexBuffer &gt;</type>
      <name>m_IndexBuffer</name>
      <anchorfile>class_real_engine_1_1_vertex_array.html</anchorfile>
      <anchor>a0d71acd04dc028cac950fcf440e32526</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RealEngine::VertexBuffer</name>
    <filename>class_real_engine_1_1_vertex_buffer.html</filename>
    <base>RealEngine::Utils::Buffer</base>
    <member kind="function">
      <type>void</type>
      <name>SetLayout</name>
      <anchorfile>class_real_engine_1_1_vertex_buffer.html</anchorfile>
      <anchor>a1991d1d244261c38bfb1d0e85cded23b</anchor>
      <arglist>(const BufferAttributes &amp;attributes)</arglist>
    </member>
    <member kind="function">
      <type>const BufferAttributes &amp;</type>
      <name>GetLayout</name>
      <anchorfile>class_real_engine_1_1_vertex_buffer.html</anchorfile>
      <anchor>a9f1b748f322e498c90fe1ea3c04c4b4e</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>BufferAttributes</type>
      <name>m_Attributes</name>
      <anchorfile>class_real_engine_1_1_vertex_buffer.html</anchorfile>
      <anchor>a2627ff9ee7e3d4d2973ee97cd46171e9</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RealEngine::Window</name>
    <filename>class_real_engine_1_1_window.html</filename>
    <member kind="function">
      <type></type>
      <name>Window</name>
      <anchorfile>class_real_engine_1_1_window.html</anchorfile>
      <anchor>a86f32dda2a1db54bc1bab473a7657c5c</anchor>
      <arglist>()=default</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Window</name>
      <anchorfile>class_real_engine_1_1_window.html</anchorfile>
      <anchor>a08edfe4a73551406242ac1500bc87837</anchor>
      <arglist>()=default</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Init</name>
      <anchorfile>class_real_engine_1_1_window.html</anchorfile>
      <anchor>af18dcd15651f32d610173d4e5362ef7e</anchor>
      <arglist>(const char *title, int width, int height)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Shutdown</name>
      <anchorfile>class_real_engine_1_1_window.html</anchorfile>
      <anchor>ab49126ba03620761823c6911a376d5f8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>OnUpdate</name>
      <anchorfile>class_real_engine_1_1_window.html</anchorfile>
      <anchor>a567ac3f83315ebc854a88c7c679203cd</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>GetVsync</name>
      <anchorfile>class_real_engine_1_1_window.html</anchorfile>
      <anchor>ac1a4766ce32c8033c962b38f2b8c7f27</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetVSync</name>
      <anchorfile>class_real_engine_1_1_window.html</anchorfile>
      <anchor>a84d8ee51c490af46f52ee3c508bf75e0</anchor>
      <arglist>(bool enabled)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>HideCursor</name>
      <anchorfile>class_real_engine_1_1_window.html</anchorfile>
      <anchor>a6454c984054d163c388f945ff1f0bbb6</anchor>
      <arglist>(bool hide)</arglist>
    </member>
    <member kind="function">
      <type>GLFWwindow *</type>
      <name>GetNativeWindow</name>
      <anchorfile>class_real_engine_1_1_window.html</anchorfile>
      <anchor>ab1a61b67998cb64acaf03f4ecc304d61</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>const float</type>
      <name>GetDeltaTime</name>
      <anchorfile>class_real_engine_1_1_window.html</anchorfile>
      <anchor>a20344208777dc38de2e01ea31e44d2d8</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetWidth</name>
      <anchorfile>class_real_engine_1_1_window.html</anchorfile>
      <anchor>adf912d4d54175f6fdebba750d2899107</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetHeight</name>
      <anchorfile>class_real_engine_1_1_window.html</anchorfile>
      <anchor>aabafcb434ff0479615d09ae9227d8baa</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>float</type>
      <name>GetScale</name>
      <anchorfile>class_real_engine_1_1_window.html</anchorfile>
      <anchor>a5eb61776691e0675c16a5b17dc8740ee</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>SetEventCallback</name>
      <anchorfile>class_real_engine_1_1_window.html</anchorfile>
      <anchor>a5a0d115736e8abc4ea9b4b495e09c8a7</anchor>
      <arglist>(const std::function&lt; void(Event &amp;)&gt; &amp;callback)</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>std::function&lt; void(Event &amp;)&gt;</type>
      <name>m_EventCallback</name>
      <anchorfile>class_real_engine_1_1_window.html</anchorfile>
      <anchor>a96e65d7db08ad60544a6636ca64f0ad1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>GLFWwindow *</type>
      <name>m_Window</name>
      <anchorfile>class_real_engine_1_1_window.html</anchorfile>
      <anchor>aec5003771217c723eda9917f5ee0a351</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>int</type>
      <name>m_Width</name>
      <anchorfile>class_real_engine_1_1_window.html</anchorfile>
      <anchor>a4b8515afd32a26bd7dcbbe5e178f366f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>int</type>
      <name>m_Height</name>
      <anchorfile>class_real_engine_1_1_window.html</anchorfile>
      <anchor>a79c1ca080f6cb53d04225d6cb34e5e42</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>bool</type>
      <name>m_Vsync</name>
      <anchorfile>class_real_engine_1_1_window.html</anchorfile>
      <anchor>af16fbb330030e717d908eefa1cb8a6f9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>float</type>
      <name>m_DeltaTime</name>
      <anchorfile>class_real_engine_1_1_window.html</anchorfile>
      <anchor>a0fb1e629883359cd1830c74b873e7b9b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>float</type>
      <name>m_LastFrameTime</name>
      <anchorfile>class_real_engine_1_1_window.html</anchorfile>
      <anchor>a782884e6482ac463eb31718336e077ba</anchor>
      <arglist></arglist>
    </member>
    <member kind="friend" protection="private">
      <type>friend class</type>
      <name>Application</name>
      <anchorfile>class_real_engine_1_1_window.html</anchorfile>
      <anchor>a23f25bcc02a0e94c2f5a4188496b04d0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RealEngine::WindowCloseEvent</name>
    <filename>class_real_engine_1_1_window_close_event.html</filename>
    <base>RealEngine::Event</base>
    <member kind="function">
      <type></type>
      <name>WindowCloseEvent</name>
      <anchorfile>class_real_engine_1_1_window_close_event.html</anchorfile>
      <anchor>ac544bdeb0324c04f252edf492e42d19a</anchor>
      <arglist>()=default</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RealEngine::WindowRescaledEvent</name>
    <filename>class_real_engine_1_1_window_rescaled_event.html</filename>
    <base>RealEngine::Event</base>
    <member kind="function">
      <type></type>
      <name>WindowRescaledEvent</name>
      <anchorfile>class_real_engine_1_1_window_rescaled_event.html</anchorfile>
      <anchor>a255daebcbe336f7bc9de2025149f0a9a</anchor>
      <arglist>(float scale)</arglist>
    </member>
    <member kind="function">
      <type>float</type>
      <name>GetScale</name>
      <anchorfile>class_real_engine_1_1_window_rescaled_event.html</anchorfile>
      <anchor>a012bcd93b88b539e8d2806846c8d6799</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>ToString</name>
      <anchorfile>class_real_engine_1_1_window_rescaled_event.html</anchorfile>
      <anchor>a8b9a7657a546c79834e7036e376b9769</anchor>
      <arglist>() const override</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>float</type>
      <name>m_Scale</name>
      <anchorfile>class_real_engine_1_1_window_rescaled_event.html</anchorfile>
      <anchor>a93789864140ace4879790ee5f1e32f5d</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RealEngine::WindowResizeEvent</name>
    <filename>class_real_engine_1_1_window_resize_event.html</filename>
    <base>RealEngine::Event</base>
    <member kind="function">
      <type></type>
      <name>WindowResizeEvent</name>
      <anchorfile>class_real_engine_1_1_window_resize_event.html</anchorfile>
      <anchor>a19903db8489ec9d76895ac2d4770f86c</anchor>
      <arglist>(unsigned int width, unsigned int height)</arglist>
    </member>
    <member kind="function">
      <type>unsigned int</type>
      <name>GetWidth</name>
      <anchorfile>class_real_engine_1_1_window_resize_event.html</anchorfile>
      <anchor>a09e442783c7d957315d75e6d18bd92ac</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>unsigned int</type>
      <name>GetHeight</name>
      <anchorfile>class_real_engine_1_1_window_resize_event.html</anchorfile>
      <anchor>ae72a4048c182110fa7b172e77ec1f593</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>ToString</name>
      <anchorfile>class_real_engine_1_1_window_resize_event.html</anchorfile>
      <anchor>a4fd67694833042cb12a0155ca7572f9c</anchor>
      <arglist>() const override</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>unsigned int</type>
      <name>m_Width</name>
      <anchorfile>class_real_engine_1_1_window_resize_event.html</anchorfile>
      <anchor>a8c51d421a1de7df39d98ab587bf28e62</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>unsigned int</type>
      <name>m_Height</name>
      <anchorfile>class_real_engine_1_1_window_resize_event.html</anchorfile>
      <anchor>abc749f8cb052d88c8213ed1369f1b1b6</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="namespace">
    <name>RealEngine</name>
    <filename>namespace_real_engine.html</filename>
    <namespace>RealEngine::Utils</namespace>
    <class kind="class">RealEngine::Application</class>
    <class kind="struct">RealEngine::ApplicationCommandLineArgs</class>
    <class kind="struct">RealEngine::ApplicationSpecification</class>
    <class kind="struct">RealEngine::BufferAttribute</class>
    <class kind="struct">RealEngine::BufferAttributes</class>
    <class kind="class">RealEngine::Camera</class>
    <class kind="class">RealEngine::CommandBuffer</class>
    <class kind="class">RealEngine::DataType</class>
    <class kind="class">RealEngine::EditorCamera</class>
    <class kind="class">RealEngine::Event</class>
    <class kind="class">RealEngine::EventDispatcher</class>
    <class kind="class">RealEngine::Framebuffer</class>
    <class kind="struct">RealEngine::FramebufferAttachmentSpecification</class>
    <class kind="struct">RealEngine::FramebufferSpecification</class>
    <class kind="struct">RealEngine::FramebufferTextureSpecification</class>
    <class kind="class">RealEngine::GeneralManager</class>
    <class kind="class">RealEngine::ImGuiLayer</class>
    <class kind="class">RealEngine::IndexBuffer</class>
    <class kind="class">RealEngine::Input</class>
    <class kind="class">RealEngine::KeyPressedEvent</class>
    <class kind="class">RealEngine::KeyReleasedEvent</class>
    <class kind="class">RealEngine::Layer</class>
    <class kind="class">RealEngine::LayerStack</class>
    <class kind="class">RealEngine::Log</class>
    <class kind="class">RealEngine::MouseButtonPressedEvent</class>
    <class kind="class">RealEngine::MouseButtonReleasedEvent</class>
    <class kind="class">RealEngine::MouseMovedEvent</class>
    <class kind="class">RealEngine::MouseScrolledEvent</class>
    <class kind="class">RealEngine::PathHash</class>
    <class kind="class">RealEngine::RenderCommands</class>
    <class kind="class">RealEngine::Renderer</class>
    <class kind="class">RealEngine::Shader</class>
    <class kind="struct">RealEngine::ShaderProcessing</class>
    <class kind="class">RealEngine::ShaderStorageBuffer</class>
    <class kind="class">RealEngine::StringHash</class>
    <class kind="class">RealEngine::Texture2D</class>
    <class kind="class">RealEngine::Texture2DArray</class>
    <class kind="struct">RealEngine::Texture2DArrayCreateInfo</class>
    <class kind="class">RealEngine::TextureManager</class>
    <class kind="class">RealEngine::UniformBuffer</class>
    <class kind="class">RealEngine::UUID</class>
    <class kind="class">RealEngine::VertexArray</class>
    <class kind="class">RealEngine::VertexBuffer</class>
    <class kind="class">RealEngine::Window</class>
    <class kind="class">RealEngine::WindowCloseEvent</class>
    <class kind="class">RealEngine::WindowRescaledEvent</class>
    <class kind="class">RealEngine::WindowResizeEvent</class>
    <member kind="typedef">
      <type>std::unique_ptr&lt; T &gt;</type>
      <name>Scope</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>a659849400c2c5a6cf615bc3e0de0a208</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::shared_ptr&lt; T &gt;</type>
      <name>Ref</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>a20de6237da7daee7e22c19cfda1195ba</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::weak_ptr&lt; T &gt;</type>
      <name>Weak_Ref</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>a221548123622d822f7604087c303d75b</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>uint32_t</type>
      <name>KeyCode</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>a813e1c4630bd8c6cfb0851eb0627026c</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>uint16_t</type>
      <name>MouseCode</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>afa258f99d87306ce10a7523c3a6a207e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>Key</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Space</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7a08034dc00200547ab15c246fcdd17cc9</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Apostrophe</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7a4decef888621c22108e3f2a84fe8b426</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Comma</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7aa687debe997a723a5b3296c65ef62acc</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Minus</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7a09294e0252a142a6b14fe8d1a803a403</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Period</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7a07b098ca4f4c4e2eeed93a097586315f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Slash</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7aef3e571b8521a12818298a2f4be0d664</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>D0</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7a4aec3f7b1d1b879f62bfaafba6d04131</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>D1</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7a57fae34a887e0ec2fab67f78a2a52b52</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>D2</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7aca492d8b679a0002f3ef1d0d6f2defed</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>D3</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7aaeaf329d794cc2b19cb3430126b7dccd</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>D4</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7aa728c78b4e8f53e81e85543311ed3e37</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>D5</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7a560361ff3382bd52f6b543174a86e501</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>D6</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7a86dd9fab83e0eed92cb82f1efb2e5730</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>D7</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7a6327bdb0157ea064326868e24e6b6831</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>D8</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7a7e5f4bad5d1611f6ed5800603398fbbe</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>D9</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7ae7fe797688a889287dc086b914bcc2d1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Semicolon</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7a081d9551b6f1823093eb8e3e08eeacba</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Equal</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7a3bda6b2858b1d602c7639d90d12e3cc2</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>A</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7adeeecefabc44f7d88046dd66cd87a1f5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>B</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7a1b574d84fbdec11c82ea536f90f78c23</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>C</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7aec8451e5836d879c3b2c24fca1ea0081</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>D</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7a584d6c2efb92e1e8226a8fd0baf6f306</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>E</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7a49eae8a1b50e3c6d3448c543566eae63</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>F</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7a30bdc92bc3ed47e7f7d5d0923580960b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>G</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7a012b8336354f899b09c51e7fbb70115a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>H</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7ae3a5d206c200c7f676448ff2ba95136a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>I</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7ad0fa440e2b4b7cc4b77b924628656049</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>J</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7a122f06be2490a03d55990ce32de16d80</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>K</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7adb6f0311274bfbd450fc8eb2b8a5fd05</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>L</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7a91a05ae51c0c39548e5174994cbd98b4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>M</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7a27b1eb21703c66945e2ad5b4042958bf</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>N</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7a0a76176483840a685aabbbe9319cbffb</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>O</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7a189897f302f61f1a49255d9dd673433c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>P</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7a776887a6173328561cfd5e30eb29f4fa</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Q</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7a2f3b49a44a23b8b0cca8ea65b6b1b38a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>R</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7aac2a15a77dad968da2fb96e35aea15c4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>S</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7a22e239ce5af32148c14ba43168078a31</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>T</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7a01bbb5bef29455c788b605262bd4b930</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>U</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7a96dcebb733274dbd1053d371edff7ce6</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>V</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7a1b7f02598866be285d092d8aba68c119</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>W</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7a1937bb8c2a4da38cbc180c9ed7d322b1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>X</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7aaed970c25f138ca976f24e90086eb3c2</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Y</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7a2a366dd09944d7eb5a3532d6ef20b67f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Z</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7a6fa0fdcb855638b867a761cace05f2bd</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>LeftBracket</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7a6b4fbce102ab34411d6c1991e5dcd57e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Backslash</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7a1c6539bbc62b055903e91696e581b225</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>RightBracket</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7ab8ba04cb62a2b28661b4aceeb5c44ffe</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>GraveAccent</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7a86a87ca29a34e817100c7b525800152b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>World1</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7ab137bea83d9f6fff49094ee0a2c2d0f1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>World2</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7a68a99c35c198e089c28728063500264c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Escape</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7a572664528a2641e370b939c7a2ae222f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Enter</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7a193f187be3e0acbeab8b4148bdf9643e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Tab</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7a909787468f11df0e93d45f360fedaf00</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Backspace</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7a2dd3362fc95a297ff29265ce64f4cd14</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Insert</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7a669191bd85b73ccde140d9d6c617c9bb</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Delete</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7a777c0e5b65c39c5d3189d3ca55eeeb56</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Right</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7af8f6cc806cbe1e08358b6424720cfaa7</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Left</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7adb80feca818d790371954286c1fa465d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Down</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7a59ff5b21224bcb65a610b4cb86f6b8d6</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Up</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7a1a2d71ed2eda55ec9db60b0c7e4891df</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>PageUp</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7a47d6c14d2ffaa124b98e3838ef42dbb3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>PageDown</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7a0d6dcc62368a95e695b85351c42fa150</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Home</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7aa7f65ab0dfa0f6182bb5c483445d74a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>End</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7a8bde085e655f8ccd465e9fef82aa96f6</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CapsLock</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7ab44b40061b518d6c2b7df86bb170bd57</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ScrollLock</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7ab302427eb17431fcdc4b30124c01eceb</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>NumLock</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7ab1d6cf76172e6d06e7103ce46bad3caf</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>PrintScreen</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7ab7934034440189cc277e8d7f57700a78</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Pause</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7aa37ada54cf2a45d9b1b35c108526aaf2</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>F1</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7ab4489e2cb0130701ffc7fd8a29fd674f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>F2</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7a0227c1e09b1d314a48a0781a6f3273ae</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>F3</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7ada594607bad2772fd1707d85ae735a34</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>F4</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7ac38ff48b2b5e5d5e8df476c32ed7977c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>F5</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7a7aa0163ba7d74c466b19625c459ca7ea</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>F6</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7a1f039a3d23bd5c8ee32ecca0c8cdf463</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>F7</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7a97697d0d4768c6d9427df8b6ef27353d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>F8</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7a8cc1eeb70abc93926940e511c84523e2</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>F9</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7a8b8d37c1cd24013dbeb78be6bfde0bc7</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>F10</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7ad7a5964d425e5eb58c44c093d3c9b9ac</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>F11</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7a875b85d1fc9a07a6586bc2a05a467f34</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>F12</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7a2a0407a888d4da13274fcc4fbbe97c5c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>F13</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7a7e2a52f1b80b25d060b6878bb765a611</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>F14</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7af5eec59fd5e87e2bbe56c6c0a77e61ae</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>F15</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7a643c2bfa94e7d73048514fef5533f15a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>F16</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7a88cca13e35ebd71466454be4c14057aa</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>F17</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7ad49a098628f51c991379d59ce9aceac2</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>F18</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7ad027677b2ade5aa2d5914112dfa1b9b6</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>F19</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7a9fcab6b5127b1c0cd7ba65967bac85b7</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>F20</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7a260c21c35b16b2129e0a24a28a78307c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>F21</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7a7ea07246b3290910246a380bd16de512</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>F22</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7a7f1d8694116c1cfa72c5e6a6ed3c0fcf</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>F23</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7ae1bc2d38ac1bd348ed63dbe269574766</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>F24</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7aaaeb14b6a04e97b72449672cc6d901e1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>F25</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7a002dfc7db6bc7e4bf48fb7a662e89cac</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>KP0</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7ae1fb4e756c328edd1662385f3011ba91</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>KP1</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7af20b1767cf183bf9be7d1c1f901b2fa7</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>KP2</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7ab750f28924678a66dc6d07729be5b040</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>KP3</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7a14c638837d394336d1137a309d75d5eb</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>KP4</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7aeaaac1253df6fc30bd450beb9ce4e6a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>KP5</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7a4b8ac8653ad042a1afe0abfe9f80bd83</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>KP6</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7a5c39f5fcbf50396600159ed7623871d3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>KP7</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7ac962b7271cf6943b68c74afdc85e9d30</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>KP8</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7a55a491985aa6dc46ecaf21ccccddbf9a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>KP9</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7a4beadcc32029cde48ae4338b461d9be7</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>KPDecimal</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7adca2e12b0c1968bcaa901e723ffa2932</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>KPDivide</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7acb53017c229c8ef9c980e241f4a556e3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>KPMultiply</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7ade115c7c4cee6f7cbb77b249afe0a53d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>KPSubtract</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7a492290db4b20c0bec5c6e73120e70835</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>KPAdd</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7a0cf93c12e83c0173d4dffa5246ca13fe</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>KPEnter</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7a15d88412313d907768870eeccc39f04c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>KPEqual</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7a112c7ddb1ad3257deb420d31b024bf6e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>LeftShift</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7a2937d1dac20a949b382f2c57aeafb1c3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>LeftControl</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7a88b651dc3fa95186dde76a70628ba340</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>LeftAlt</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7a652a7c494bdbc9c58a7498c50b8e2c26</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>LeftSuper</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7adf1e9fab0577e87b5bfdbf3a551a77e2</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>RightShift</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7a284f73f0f531896c1fab46284d755ca4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>RightControl</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7a3013b50a7fe992ded804be7716494e46</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>RightAlt</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7a2686e9442440ddbc8d108dd8611ff9db</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>RightSuper</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7af2520b2de1aa7b6f037d641808422728</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Menu</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>acaedef57d86a62b136dd733a793672a7a878baf235127bc23b850a52c9e752332</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>Mouse</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>a443b5e16d8bbe86357084c8010519836</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Button0</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>a443b5e16d8bbe86357084c8010519836a40d2c6ec2c57979e676e658cd31f2570</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Button1</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>a443b5e16d8bbe86357084c8010519836aaf1e5c3ed2c648d87f34c846adc92eb0</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Button2</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>a443b5e16d8bbe86357084c8010519836aa3460f732dbe9f87fc0e66fcd5585e79</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Button3</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>a443b5e16d8bbe86357084c8010519836a90e2750ca1faa9e1422babce604e0379</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Button4</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>a443b5e16d8bbe86357084c8010519836a809747d69849e00375b8e16677598b92</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Button5</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>a443b5e16d8bbe86357084c8010519836af4f2505a26644ecbe934df52b7b6571f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Button6</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>a443b5e16d8bbe86357084c8010519836af6fd85053ba2746876a2926c1339585d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Button7</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>a443b5e16d8bbe86357084c8010519836ac266d7e40152f0a16f9f2ac931fa8276</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ButtonLast</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>a443b5e16d8bbe86357084c8010519836a755cb2eccde24b5d2b971378275c69e1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ButtonLeft</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>a443b5e16d8bbe86357084c8010519836a1b3e9185f58fe127f3c7e7fb60aee16b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ButtonRight</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>a443b5e16d8bbe86357084c8010519836ae57130939a40e6951d323d7e30b86a63</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ButtonMiddle</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>a443b5e16d8bbe86357084c8010519836a3b3f72e0ebcc3ab6235daf7e1cb949fa</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>EventType</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>af7772263466c56c32900837e00fdf9c9</anchor>
      <arglist></arglist>
      <enumvalue file="namespace_real_engine.html" anchor="af7772263466c56c32900837e00fdf9c9a6adf97f83acf6453d4a6a4b1070f3754">None</enumvalue>
      <enumvalue file="namespace_real_engine.html" anchor="af7772263466c56c32900837e00fdf9c9ac984201d37197ab297a14d19efee4b07">WindowClose</enumvalue>
      <enumvalue file="namespace_real_engine.html" anchor="af7772263466c56c32900837e00fdf9c9a9f8f27bff2915738c4fe1b970e12f89c">WindowResize</enumvalue>
      <enumvalue file="namespace_real_engine.html" anchor="af7772263466c56c32900837e00fdf9c9a51e5b6b7987d9e5d9142d5fd79aea5fb">WindowRescaled</enumvalue>
      <enumvalue file="namespace_real_engine.html" anchor="af7772263466c56c32900837e00fdf9c9a7349f643d689997b7c54bf93e4095f5c">MouseButtonPressed</enumvalue>
      <enumvalue file="namespace_real_engine.html" anchor="af7772263466c56c32900837e00fdf9c9a7584c169de594c27f00084b93186fd7c">MouseButtonReleased</enumvalue>
      <enumvalue file="namespace_real_engine.html" anchor="af7772263466c56c32900837e00fdf9c9ac2770ad109c8063ce69a3608a9a16c08">MouseMoved</enumvalue>
      <enumvalue file="namespace_real_engine.html" anchor="af7772263466c56c32900837e00fdf9c9a50edb169910041bb3c06f6e8322d74c1">MouseScrolled</enumvalue>
      <enumvalue file="namespace_real_engine.html" anchor="af7772263466c56c32900837e00fdf9c9ac17e6984c1e5a887a49831beadee6bca">KeyPressed</enumvalue>
      <enumvalue file="namespace_real_engine.html" anchor="af7772263466c56c32900837e00fdf9c9a4a77f07c8ad223b71ab4ce78a63841ab">KeyReleased</enumvalue>
      <enumvalue file="namespace_real_engine.html" anchor="af7772263466c56c32900837e00fdf9c9afa5b4c281fd62f3c9affa8cbbd9d74aa">PannelFolderSelect</enumvalue>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>FramebufferTextureFormat</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>ad91fcb4ca8a42328287692f94b37d2b1</anchor>
      <arglist></arglist>
      <enumvalue file="namespace_real_engine.html" anchor="ad91fcb4ca8a42328287692f94b37d2b1a6adf97f83acf6453d4a6a4b1070f3754">None</enumvalue>
      <enumvalue file="namespace_real_engine.html" anchor="ad91fcb4ca8a42328287692f94b37d2b1ab4b279046a02077466fa26cabb00c642">RGBA8</enumvalue>
      <enumvalue file="namespace_real_engine.html" anchor="ad91fcb4ca8a42328287692f94b37d2b1a2849effb989cbdcfb4b9eb143fd826aa">RED_INTEGER</enumvalue>
      <enumvalue file="namespace_real_engine.html" anchor="ad91fcb4ca8a42328287692f94b37d2b1a0768a7b4ae12f44fd7d2b5320256b4b8">DEPTH24_STENCIL8</enumvalue>
      <enumvalue file="namespace_real_engine.html" anchor="ad91fcb4ca8a42328287692f94b37d2b1a675056ad1441b6375b2c5abd48c27ef1">Depth</enumvalue>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>ShaderTypes</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>a58ad3b3a5634ee278b824152386b0afa</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Fragment</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>a58ad3b3a5634ee278b824152386b0afaa481d60955ceafefbbf51a2680810e685</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Vertex</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>a58ad3b3a5634ee278b824152386b0afaa16ab81f3daf9c5e2c18131c0838ccfdc</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Compute</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>a58ad3b3a5634ee278b824152386b0afaa058235174986d8f16ae34e60f6f989f3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Unknown</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>a58ad3b3a5634ee278b824152386b0afaacbb419eb5982b6498ce7e4312787b034</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>TextureFormat</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>ac6c8dccd3484be21a944c95c4855dfb1</anchor>
      <arglist></arglist>
      <enumvalue file="namespace_real_engine.html" anchor="ac6c8dccd3484be21a944c95c4855dfb1ab50339a10e1de285ac99d4c3990b8693">NONE</enumvalue>
      <enumvalue file="namespace_real_engine.html" anchor="ac6c8dccd3484be21a944c95c4855dfb1aa2d9547b5d3dd9f05984475f7c926da0">RED</enumvalue>
      <enumvalue file="namespace_real_engine.html" anchor="ac6c8dccd3484be21a944c95c4855dfb1abac953e88f6d79514b0b6fc42eb6f3b7">RG</enumvalue>
      <enumvalue file="namespace_real_engine.html" anchor="ac6c8dccd3484be21a944c95c4855dfb1a2ad5640ebdec72fc79531d1778c6c2dc">BGR</enumvalue>
      <enumvalue file="namespace_real_engine.html" anchor="ac6c8dccd3484be21a944c95c4855dfb1a889574aebacda6bfd3e534e2b49b8028">RGB</enumvalue>
      <enumvalue file="namespace_real_engine.html" anchor="ac6c8dccd3484be21a944c95c4855dfb1aea3495a278957dc58165e48a8945469f">RGBA</enumvalue>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>TextureDataType</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>ab1df9061d29b50d6faa679ad25b18155</anchor>
      <arglist></arglist>
      <enumvalue file="namespace_real_engine.html" anchor="ab1df9061d29b50d6faa679ad25b18155ab50339a10e1de285ac99d4c3990b8693">NONE</enumvalue>
      <enumvalue file="namespace_real_engine.html" anchor="ab1df9061d29b50d6faa679ad25b18155a8151b1ac85e561145f811aeb8c927214">RED8</enumvalue>
      <enumvalue file="namespace_real_engine.html" anchor="ab1df9061d29b50d6faa679ad25b18155ac1e3b8b6a17780530cb2da0410eb43b4">RED8I</enumvalue>
      <enumvalue file="namespace_real_engine.html" anchor="ab1df9061d29b50d6faa679ad25b18155a6ba888f0cc7873140036a41e39ea5e51">RED8UI</enumvalue>
      <enumvalue file="namespace_real_engine.html" anchor="ab1df9061d29b50d6faa679ad25b18155a1e0bcb7c8d1365384626fa782bab06ea">RED16</enumvalue>
      <enumvalue file="namespace_real_engine.html" anchor="ab1df9061d29b50d6faa679ad25b18155ab28bc8c5d04605a9d08fdd5e4d973594">RED16I</enumvalue>
      <enumvalue file="namespace_real_engine.html" anchor="ab1df9061d29b50d6faa679ad25b18155aa762509ced97a0c0565fe65e01bc3826">RED16UI</enumvalue>
      <enumvalue file="namespace_real_engine.html" anchor="ab1df9061d29b50d6faa679ad25b18155a7342d50332288317a9d655d659715fd2">RED32</enumvalue>
      <enumvalue file="namespace_real_engine.html" anchor="ab1df9061d29b50d6faa679ad25b18155a6f9a7b45b24bcaaac9d1644782ded2f7">RED32I</enumvalue>
      <enumvalue file="namespace_real_engine.html" anchor="ab1df9061d29b50d6faa679ad25b18155a03d777852592ff3a820992deccbb4809">RED32UI</enumvalue>
      <enumvalue file="namespace_real_engine.html" anchor="ab1df9061d29b50d6faa679ad25b18155a0367a93b9e3e7aa2fbe9802d80298e46">RG8</enumvalue>
      <enumvalue file="namespace_real_engine.html" anchor="ab1df9061d29b50d6faa679ad25b18155af16a55975b8a8daa365e5b3cb116a001">RG8I</enumvalue>
      <enumvalue file="namespace_real_engine.html" anchor="ab1df9061d29b50d6faa679ad25b18155a65264dd5d010ab021cbec10f07f97ed5">RG8UI</enumvalue>
      <enumvalue file="namespace_real_engine.html" anchor="ab1df9061d29b50d6faa679ad25b18155a2b66caa416f0a28686ade3fc30ab223a">RG16</enumvalue>
      <enumvalue file="namespace_real_engine.html" anchor="ab1df9061d29b50d6faa679ad25b18155af0c6bc16df3d36b62adc241a797148de">RG16I</enumvalue>
      <enumvalue file="namespace_real_engine.html" anchor="ab1df9061d29b50d6faa679ad25b18155a4475a780df31a86ece088a8aac082b12">RG16UI</enumvalue>
      <enumvalue file="namespace_real_engine.html" anchor="ab1df9061d29b50d6faa679ad25b18155aa8725115efc714421823b7397f9c130c">RG32</enumvalue>
      <enumvalue file="namespace_real_engine.html" anchor="ab1df9061d29b50d6faa679ad25b18155a56014c7d6ebfadbff4d0d4d3c20a0243">RG32I</enumvalue>
      <enumvalue file="namespace_real_engine.html" anchor="ab1df9061d29b50d6faa679ad25b18155ac16ead63f9b07b5c97635edac05412cd">RG32UI</enumvalue>
      <enumvalue file="namespace_real_engine.html" anchor="ab1df9061d29b50d6faa679ad25b18155a165c6379d01617e12de274a3952efa63">RGB8</enumvalue>
      <enumvalue file="namespace_real_engine.html" anchor="ab1df9061d29b50d6faa679ad25b18155a57a36f0c89bfa81cdd9a69e2ad2df08b">RGB8I</enumvalue>
      <enumvalue file="namespace_real_engine.html" anchor="ab1df9061d29b50d6faa679ad25b18155afc5e2f0963f0ce3529e8aee36d827bbd">RGB8UI</enumvalue>
      <enumvalue file="namespace_real_engine.html" anchor="ab1df9061d29b50d6faa679ad25b18155a1cd42e2af35bdfb43d791f8cecdce4a4">RGB16</enumvalue>
      <enumvalue file="namespace_real_engine.html" anchor="ab1df9061d29b50d6faa679ad25b18155aff7632ef49d4bbe6b35050ac957a04c8">RGB16I</enumvalue>
      <enumvalue file="namespace_real_engine.html" anchor="ab1df9061d29b50d6faa679ad25b18155adfb1f628557b0014586b94400f06777b">RGB16UI</enumvalue>
      <enumvalue file="namespace_real_engine.html" anchor="ab1df9061d29b50d6faa679ad25b18155ace70a5db6685e6d210c3f905a8fa7d4c">RGB32</enumvalue>
      <enumvalue file="namespace_real_engine.html" anchor="ab1df9061d29b50d6faa679ad25b18155a8305c7f5432d31774cceb858c966b22e">RGB32I</enumvalue>
      <enumvalue file="namespace_real_engine.html" anchor="ab1df9061d29b50d6faa679ad25b18155ae240d3e394b6a7cfa467efe512e96bb4">RGB32UI</enumvalue>
      <enumvalue file="namespace_real_engine.html" anchor="ab1df9061d29b50d6faa679ad25b18155ab4b279046a02077466fa26cabb00c642">RGBA8</enumvalue>
      <enumvalue file="namespace_real_engine.html" anchor="ab1df9061d29b50d6faa679ad25b18155ab99d001604e415e4ea7f107daaffd6dd">RGBA8I</enumvalue>
      <enumvalue file="namespace_real_engine.html" anchor="ab1df9061d29b50d6faa679ad25b18155aeb843f86a572765b9be8a71bd9563bea">RGBA8UI</enumvalue>
      <enumvalue file="namespace_real_engine.html" anchor="ab1df9061d29b50d6faa679ad25b18155a50989efe15b375dce8ba3a5714fe2543">RGBA16</enumvalue>
      <enumvalue file="namespace_real_engine.html" anchor="ab1df9061d29b50d6faa679ad25b18155a3d8d82a913260a439bf38ed05d6d2f46">RGBA16I</enumvalue>
      <enumvalue file="namespace_real_engine.html" anchor="ab1df9061d29b50d6faa679ad25b18155ae418a751a46186248578aecf3f30a26c">RGBA16UI</enumvalue>
      <enumvalue file="namespace_real_engine.html" anchor="ab1df9061d29b50d6faa679ad25b18155ad9e8e4a9228ed56eceb29f0a1223b02b">RGBA32</enumvalue>
      <enumvalue file="namespace_real_engine.html" anchor="ab1df9061d29b50d6faa679ad25b18155a9f87275b4130dd118085dd75ee6a7ac1">RGBA32I</enumvalue>
      <enumvalue file="namespace_real_engine.html" anchor="ab1df9061d29b50d6faa679ad25b18155ac050956335d883e2f6ed07cc6b0c90d8">RGBA32UI</enumvalue>
    </member>
    <member kind="function">
      <type>Application *</type>
      <name>CreateApplication</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>a4e4e112f24635e192e4cc662d6911069</anchor>
      <arglist>(const ApplicationCommandLineArgs &amp;args)</arglist>
    </member>
    <member kind="function">
      <type>constexpr Scope&lt; T &gt;</type>
      <name>CreateScope</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>ace18f6b2e2b5319bcc16a9e3d6b0b521</anchor>
      <arglist>(Args &amp;&amp;... args)</arglist>
    </member>
    <member kind="function">
      <type>constexpr Ref&lt; T &gt;</type>
      <name>CreateRef</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>a9090a8984927181b5605993771ec6eef</anchor>
      <arglist>(Args &amp;&amp;... args)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>GLFWErrorCallback</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>aec427a62859f17dcef491639f740c7e0</anchor>
      <arglist>(int error, const char *description)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static C4_NORETURN void</type>
      <name>YAMLErrorCallBack</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>a3522d7c8636f05aff876e884d7eb4fb8</anchor>
      <arglist>(const char *msg, size_t len, ryml::Location loc, void *userData)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetYAMLErrorCallbacks</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>a2bf25543f6cdf4d6feaeac571c271020</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>OpenGLMessageCallback</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>a8e532241352c8fc008ba87305e9437fc</anchor>
      <arglist>(unsigned source, unsigned type, unsigned id, unsigned severity, int length, const char *message, const void *userParam)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static RenderData</type>
      <name>s_RenderData</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>ac94693d3c9d078a6fbd2cc3314280af9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static std::mt19937_64</type>
      <name>s_RandomEngine</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>a9abaa77b4a9e81229e841f3914e58ab8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static std::uniform_int_distribution&lt; uint64_t &gt;</type>
      <name>s_UniformDistribution</name>
      <anchorfile>namespace_real_engine.html</anchorfile>
      <anchor>aeb1615167d7ac5586c4f9f8021872f36</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="namespace">
    <name>RealEngine::Utils</name>
    <filename>namespace_real_engine_1_1_utils.html</filename>
    <class kind="class">RealEngine::Utils::Buffer</class>
    <member kind="enumeration">
      <type></type>
      <name>BufferType</name>
      <anchorfile>namespace_real_engine_1_1_utils.html</anchorfile>
      <anchor>a87c6114adedc51306f58505b87bd729d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>VertexBuffer</name>
      <anchorfile>namespace_real_engine_1_1_utils.html</anchorfile>
      <anchor>a87c6114adedc51306f58505b87bd729da1ad6b102be748b104fab4967d839237d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IndexBuffer</name>
      <anchorfile>namespace_real_engine_1_1_utils.html</anchorfile>
      <anchor>a87c6114adedc51306f58505b87bd729da9f94ad8df327d0e6424c16d16a2820cd</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ShaderStorageBuffer</name>
      <anchorfile>namespace_real_engine_1_1_utils.html</anchorfile>
      <anchor>a87c6114adedc51306f58505b87bd729dafd828a731d05a9df89cb6a60d1e4b23b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>UniformBuffer</name>
      <anchorfile>namespace_real_engine_1_1_utils.html</anchorfile>
      <anchor>a87c6114adedc51306f58505b87bd729da17dcdbebf22f072cd87b894c4734aaac</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CommandBuffer</name>
      <anchorfile>namespace_real_engine_1_1_utils.html</anchorfile>
      <anchor>a87c6114adedc51306f58505b87bd729da1ef45d2c7bab84daf48896a61b58b40a</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>GLenum</type>
      <name>GetGLType</name>
      <anchorfile>namespace_real_engine_1_1_utils.html</anchorfile>
      <anchor>a99eb8f687bf39a7615978b3485f40011</anchor>
      <arglist>(TextureDataType type)</arglist>
    </member>
  </compound>
  <compound kind="namespace">
    <name>std</name>
    <filename>namespacestd.html</filename>
    <class kind="struct">std::hash&lt; RealEngine::PathHash &gt;</class>
    <class kind="struct">std::hash&lt; RealEngine::StringHash &gt;</class>
    <class kind="struct">std::hash&lt; RealEngine::UUID &gt;</class>
  </compound>
  <compound kind="page">
    <name>index</name>
    <title>📁 RealEngine File Index</title>
    <filename>index.html</filename>
    <docanchor file="index.html" title="📁 RealEngine File Index">md__c_1_2_users_2sixde_2_documents_2_real_engine-_editor_2_real_engine_2docs_2_f_i_l_e_s</docanchor>
  </compound>
</tagfile>

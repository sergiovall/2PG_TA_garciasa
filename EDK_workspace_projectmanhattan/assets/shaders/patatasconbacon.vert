#version 330

uniform mat4 u_m_matrix;
uniform mat4 u_vp_matrix;
uniform float u_time;
uniform vec3 u_color;
uniform vec3 u_light_position;

layout (location=0) in vec3 a_pos_;
layout (location=1) in vec3 a_normal_;
layout (location=2) in vec2 a_uv_;

out vec3 pos;
out vec2 uv;
out vec3 normal;
out float visibility;
out vec3 fragPos;

const float density = 0.0007f;
const float grad = 1.5f;

void main() {

vec4 cameraDist = u_vp_matrix * u_m_matrix* vec4(a_pos_, 1.0);
  gl_Position =  u_vp_matrix * u_m_matrix* vec4(a_pos_, 1.0);

  pos = a_pos_;
  uv = a_uv_;
normal = a_normal_;
fragPos = vec3(u_m_matrix *vec4(a_pos_,1.0f));

float dist = length(cameraDist.xyz);
visibility = exp(-pow((dist * density),grad));
visibility = clamp(visibility,0.0f,1.0f);

}

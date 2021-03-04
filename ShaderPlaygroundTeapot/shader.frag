#version 330

uniform float u_time;
uniform vec3 lightPos;

out vec4 fragColor;

in vec3 normal;
in vec3 FragPos;

void main() {
  float ambient_light_strength = 0.1f;
  vec3 light_color = vec3(1.0f,1.0f,1.0f);
  vec3 teapot_color = vec3(1.0f,1.0f,1.0f);

  vec3 ambient_light = ambient_light_strength * light_color;
  vec3 a_normal = normalize(normal);
  vec3 light_direction = normalize(FragPos - lightPos);
  float diff = max(dot(a_normal, light_direction), 0.0);
  vec3 diffuse_light = diff * light_color * 2.0f;

  vec3 result = (ambient_light + diffuse_light) * teapot_color;

  fragColor = vec4(result, 1.0);

 }

#version 330

in vec3 pos;
in vec2 uv;
in vec3 normal;
in float visibility;
in vec3 fragPos;

out vec4 fragColor;

struct DirLight{
  vec3 direction;
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
  vec3 light_color;
  float light_force;
} ;

struct PointLight{
  vec3 position;
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
  vec3 light_color;
  float light_force;
  float linear;
  float constant;
  float quadratic;
};

struct SpotLight{
  vec3 position;
  vec3 direction;
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
  float light_force;
  float linear;
  float constant;
  float quadratic;
  float angle;
  vec3 light_color;
  float external_angle;
};

#define DIR_LIGHT_COUNT 1
#define POINT_LIGHT_COUNT 1
#define SPOT_LIGHT_COUNT 1

uniform int u_dir_light_count;
uniform DirLight u_dir_lights[DIR_LIGHT_COUNT];

uniform int u_point_light_count;
uniform PointLight u_point_lights[POINT_LIGHT_COUNT];

uniform int u_spot_light_count;
uniform SpotLight u_spot_lights[SPOT_LIGHT_COUNT];

uniform int u_fog_enabled;
uniform float u_time;
uniform float u_mat_bright;
uniform vec3 u_color;
uniform vec3 u_camera_pos;
uniform vec3 u_fog_color;
uniform sampler2D u_texture_color;


Vec3CalcDirLight(DirLight light, vec3 light_normal, vec3 view_direction){

  vec3 light_direction = normalize(-light.direction);

  float diffuse_strength = max(dot(normal,light_direction),0.0f);
  vec3 reflect_direction = reflect(-light_direction, normal);

  float spec = pow(max(dot(view_direction, reflect_direction),0.0f), u_mat_bright);
  vec3 specular = light.light_force * spec * light.light_color;


  vec3 ambient  = light.ambient  * vec3(texture(u_texture_color, uv )) * light.light_color;
  vec3 diffuse  = light.diffuse  * diffuse_strength * vec3(texture(u_texture_color, uv )) * light.light_color;
  vec3 specular_source = light.specular * spec * vec3(texture(u_texture_color, uv )) * light.light_color;

  return ( ambient+ diffuse+ specular_source );//
};

vec3 Vec3CalcPointLight(PointLight light, vec3 light_normal, vec3 view_direction){

  vec3 light_direction = normalize(light.position - fragPos);
  float diffuse_strength = max(dot(normal,light_direction),0.0f);
  vec3 reflect_direction = reflect(-light_direction, normal);

  float spec = pow(max(dot(view_direction, reflect_direction),0.0f), u_mat_bright);

  float dist = length( light.position - fragPos );
  float attenuate_value = (10000.0f * light.light_force * light.light_force)/(light.constant + light.linear * dist + light.quadratic * (dist*dist));

  vec3 ambient  = light.ambient  * vec3(texture(u_texture_color, uv )) * attenuate_value * light.light_color;
  vec3 diffuse  = light.diffuse  * diffuse_strength * vec3(texture(u_texture_color, uv )) * attenuate_value * light.light_color;
  vec3 specular_source = light.specular * spec * vec3(texture(u_texture_color, uv ))* attenuate_value * light.light_color;

  return ( ambient + diffuse+ specular_source);//
};

vec3 Vec3CalcSpotLight(SpotLight light, vec3 light_normal, vec3 view_direction){

  vec3 light_direction = normalize(light.position - fragPos);
  float angle = dot(light_direction, normalize(-light.direction));
  float cos_light = cos(light.angle);
  float dist_to_border = cos_light - cos(light.external_angle);
  float light_intensity = clamp((cos(light.external_angle)-angle)/dist_to_border,0.0,1.0);

  if(angle < cos_light){

    vec3 ambient  = light.ambient  * vec3(texture(u_texture_color, uv )) * light.light_color;

    float diffuse_strength = max(dot(normal, light_direction), 0.0);
    vec3 diffuse  = light.diffuse  * diffuse_strength * vec3(texture(u_texture_color, uv )) * light.light_color;

    float dist = length( light.position - fragPos);
    float attenuate_value = (10000.0f * light.light_force * light.light_force)/(light.constant + light.linear * dist + light.quadratic * (dist*dist));

    vec3 reflect_direction = reflect(-light_direction, normal);
    float spec = pow(max(dot(view_direction, reflect_direction),0.0f), u_material_bright);
    vec3 specular = light.specular * spec * vec3(texture(u_texture_color, uv )) * light.light_color;

    ambient *= light_intensity;
    diffuse  *= attenuate_value * light_intensity;
    specular_source *= attenuate_value * light_intensity;
    return ( ambient + diffuse+ specular_source);
  }
  else
  {

    return vec3(0.0f);

  }

}

void main() {

  vec3 out_vector = vec3(0.0f);
  vec3 view_dir = normalize(u_camera_pos - fragPos);

  for(int i = 0; i<DIR_LIGHT_COUNT; i++){
    out_vector += Vec3CalcDirLight(u_dir_lights[i], normal, view_dir);
  }

  for(int i = 0; i<POINT_LIGHT_COUNT; i++){
    out_vector += Vec3CalcPointLight(u_point_lights[i], normal, view_dir);
  }

  for(int i = 0; i<SPOT_LIGHT_COUNT; i++){
    out_vector += Vec3CalcSpotLight(u_spot_lights[i], normal, view_dir);
  }

  fragColor = vec4(1.0f,1.0f,1.0f, 1.0f);

  if(u_fog_enabled != 0){

    fragColor = mix(vec4(u_fog_color,1.0f),fragColor, visibility);

  }


}

#stage vertex

layout (location = 0) in vec3 a_position;
layout (location = 1) in vec2 a_texcoord;
layout (location = 2) in vec2 a_normal;
layout (location = 3) in vec4 a_color;

uniform mat4 u_model;
uniform mat4 u_view_projection;
uniform vec4 u_mesh_color;

out vec4 o_color;

void main()
{
    o_color = u_mesh_color;
    gl_Position = u_view_projection * u_model * vec4(a_position, 1.0);
}

#stage fragment

in vec4 o_color;
out vec4 FragColor;

void main()
{
    FragColor = o_color;
}
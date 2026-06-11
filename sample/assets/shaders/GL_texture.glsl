#stage vertex

layout (location = 0) in vec3 a_position;
layout (location = 1) in vec2 a_texcoord;
layout (location = 2) in vec2 a_normal;
layout (location = 3) in vec4 a_color;

uniform mat4 u_model;
uniform mat4 u_view_projection;

out vec2 o_texcoord;

void main()
{
    o_texcoord = a_texcoord;
    gl_Position = u_view_projection * u_model * vec4(a_position, 1.0);
}

#stage fragment

in vec2 o_texcoord;
out vec4 FragColor;
uniform sampler2D u_texture;

void main()
{
    FragColor = texture(u_texture, o_texcoord);
}
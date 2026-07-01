#stage vertex

layout (location = 0) in vec4 a_position;
layout (location = 1) in vec2 a_texcoord;
layout (location = 2) in vec4 a_color;

uniform mat4 u_view_projection;

out vec4 o_color;
out vec2 o_texcoord;

void main()
{
    o_color = a_color;
    o_texcoord = a_texcoord;
    gl_Position = u_view_projection * a_position;
}

#stage fragment

out vec4 FragColor;
in vec4 o_color;
in vec2 o_texcoord;

uniform sampler2D u_texture;

void main()
{
    float alpha = texture(u_texture, o_texcoord).r;
    FragColor = vec4(o_color.rgb, o_color.a * alpha);
}

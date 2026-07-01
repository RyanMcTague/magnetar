#stage vertex

layout (location = 0) in vec4 a_position;
layout (location = 1) in vec2 a_texcoord;
layout (location = 2) in vec4 a_color;
layout (location = 3) in float a_texture;

uniform mat4 u_view_projection;
uniform float u_null_texcoord;

out vec4 o_color;
out vec2 o_texcoord;
out float o_texture;
out float o_null_texcoord;

void main()
{
    o_color = a_color;
    o_texcoord = a_texcoord;
    o_texture = int(a_texture);
    o_null_texcoord = u_null_texcoord;
    gl_Position = u_view_projection * a_position;
}

#stage fragment

in vec4 o_color;
in vec2 o_texcoord;
in float o_texture;
in float o_null_texcoord;

int used_texture = int(o_texture);
int null_texcoord = int(o_null_texcoord);

out vec4 FragColor;

uniform sampler2D u_texture0;

void main()
{
    if(used_texture < null_texcoord)
    {
        switch(used_texture)
        {
        case 0:
            FragColor = texture(u_texture0, o_texcoord);
            break;
        default:
            break;
        }
    }
    else
    {
        FragColor = o_color;
    }
}
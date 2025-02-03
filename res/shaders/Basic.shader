#shader vertex
#version 330 core
layout(location=0) in vec4 position;
layout(location=1) in vec2 texCoord;


out vec2 v_texCoord;
uniform mat4 u_MVP;

uniform vec3 axisPositions[6]; // 6 positions for the 3 axes (2 points per axis)
uniform vec3 axisColors[6];    // 6 colors corresponding to the 6 positions

void main()
{
    gl_Position=u_MVP * position;
    v_texCoord = texCoord;
};


#shader fragment
#version 330 core
layout(location=0) out vec4 color;
in vec2 v_texCoord;
uniform vec4 u_Color;
uniform sampler2D u_Texture;

void main()
{
    vec4 texColor = texture(u_Texture,v_texCoord);
    color =texColor;
};


#type vertex
#version 330 core
layout(location = 0) in vec3 a_Pos;

uniform mat4 u_ViewProjMat;
uniform mat4 u_ModelMat;

void main()
{
    gl_Position = u_ViewProjMat * u_ModelMat * vec4(a_Pos, 1.0);
} 





#type fragment
#version 330 core
out vec4 color;
uniform vec4 u_Color;
void main()
{
    color = u_Color;
}  
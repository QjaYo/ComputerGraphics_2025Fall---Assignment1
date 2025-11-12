//#include "box.h"
//#include <InitShader.h>
//
//Box::Box(vec3 center, vec3 size, vec4 color)
//{
//    this->center = center;
//    this->size = size;
//    this->color = color;
//    this->rot = vec3{ 0.0f, 0.0f, 0.0f };
//}
//
//void Box::append_square(Vertex a, Vertex b, Vertex c, Vertex d)
//{
//    this->vertices.push_back(a);
//    this->vertices.push_back(b);
//    this->vertices.push_back(c);
//    this->vertices.push_back(a);
//    this->vertices.push_back(c);
//    this->vertices.push_back(d);
//}
//
//void Box::append_box(vec3 center, vec3 size, vec4 color)
//{
//    vec3 dh = 0.5f * size;
//
//    Vertex front_a = { vec4{ center.x + dh.x, center.y + dh.y, center.z + dh.z, 1.0f }, color };
//    Vertex front_b = { vec4{ center.x - dh.x, center.y + dh.y, center.z + dh.z, 1.0f }, color };
//    Vertex front_c = { vec4{ center.x - dh.x, center.y - dh.y, center.z + dh.z, 1.0f }, color };
//    Vertex front_d = { vec4{ center.x + dh.x, center.y - dh.y, center.z + dh.z, 1.0f }, color };
//
//    Vertex back_a = { vec4{ center.x + dh.x, center.y + dh.y, center.z - dh.z, 1.0f }, color };
//    Vertex back_b = { vec4{ center.x - dh.x, center.y + dh.y, center.z - dh.z, 1.0f }, color };
//    Vertex back_c = { vec4{ center.x - dh.x, center.y - dh.y, center.z - dh.z, 1.0f }, color };
//    Vertex back_d = { vec4{ center.x + dh.x, center.y - dh.y, center.z - dh.z, 1.0f }, color };
//
//    append_square(front_a, front_b, front_c, front_d); // ¾Õ¸é
//    append_square(back_a, back_b, back_c, back_d);     // µÞ¸é
//    append_square(back_a, back_b, front_b, front_a);   // À­¸é
//    append_square(back_b, back_c, front_c, front_b);   // ¿ÞÂÊ¸é
//    append_square(back_c, back_d, front_d, front_c);   // ¾Æ·§¸é
//    append_square(back_d, back_a, front_a, front_d);   // ¿À¸¥ÂÊ¸é
//}
//
//void Box::initBuffers()
//{
//    // VAO
//    glGenVertexArrays(1, &VAO);
//    glBindVertexArray(VAO);
//
//    // VBO
//    glGenBuffers(1, &VBO);
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//
//    // init VBO
//    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), nullptr, GL_DYNAMIC_DRAW);
//
//    // load shaders & activate shader program
//    program = InitShader("vshader_box.glsl", "fshader_box.glsl");
//    glUseProgram(program);
//
//    // set stride
//    GLsizei stride = sizeof(Vertex);
//    // first attribute
//    GLuint vPosition = glGetAttribLocation(program, "vPosition");
//    glEnableVertexAttribArray(vPosition);
//    glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, stride, BUFFER_OFFSET(0));
//    // second attribute
//    GLuint vColor = glGetAttribLocation(program, "vColor");
//    glEnableVertexAttribArray(vColor);
//    glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, stride, BUFFER_OFFSET(sizeof(vec4)));
//
//    glBindVertexArray(0);
//}
//
//void Box::updateBuffers()
//{
//    vertices.clear();
//
//    append_box(center, size, color);
//
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_DYNAMIC_DRAW);
//}
//
//void Box::draw()
//{
//    glm::mat4 modelMatrix = buildRotMatrix(rot);
//    GLint u_model = glGetUniformLocation(program, "u_model");
//    glUniformMatrix4fv(u_model, 1, GL_FALSE, &modelMatrix[0][0]);
//
//    glBindVertexArray(VAO);
//    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
//}

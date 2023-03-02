#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/glm.hpp>
#include <vector>
#include <filesystem>

int window_width  = 1280;
int window_height = 720;

static void key_callback(GLFWwindow* /*window*/, int /*key*/, int /*scancode*/, int /*action*/, int /*mods*/)
{
}

static void mouse_button_callback(GLFWwindow* /*window*/, int /*button*/, int /*action*/, int /*mods*/)
{
}

static void scroll_callback(GLFWwindow* /*window*/, double /*xoffset*/, double /*yoffset*/)
{
}

static void cursor_position_callback(GLFWwindow* /*window*/, double /*xpos*/, double /*ypos*/)
{
}

static void size_callback(GLFWwindow* /*window*/, int width, int height)
{
    window_width  = width;
    window_height = height;
}

struct Vertex2DColor
{
    glm::vec2 m_position;
    glm::vec3 m_color;

    Vertex2DColor(){
        m_position = glm::vec2(0.);
        m_color = glm::vec3(1.);
    };
    Vertex2DColor(glm::vec2 position, glm::vec3 color){
        m_position = position;
        m_color = color;
    }
    Vertex2DColor(glm::vec2 position){
        m_position = position;
    }
};

struct Vertex2DUV
{
    glm::vec2 m_position;
    glm::vec2 m_texture;

    Vertex2DUV(glm::vec2 position, glm::vec2 texture){
        m_position = position;
        m_texture = texture;
    }
};
glm::mat3 translate(float tx, float ty){
  return glm::mat3(glm::vec3(1, 0, 0), glm::vec3(0, 1, 0), glm::vec3(tx, ty, 1));
}

glm::mat3 scale(float sx, float sy){
  return glm::mat3(glm::vec3(sx, 0, 0), glm::vec3(0, sy, 0), glm::vec3(0, 0, 1));
}

glm::mat3 rotate(float a){
  return glm::mat3(glm::vec3(cos(glm::radians(a)), sin(glm::radians(a)), 0), glm::vec3(-sin(glm::radians(a)),cos(glm::radians(a)) , 0), glm::vec3(0, 0, 1));
}


int main([[maybe_unused]]int argc, [[maybe_unused]] char* argv[])
{
    /* Initialize the library */
    if (!glfwInit()) {
        return -1;
    }


    /* Create a window and its OpenGL context */
#ifdef __APPLE__
    /* We need to explicitly ask for a 3.3 context on Mac */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif
    GLFWwindow* window = glfwCreateWindow(window_width, window_height, "TP1", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Intialize glad (loads the OpenGL functions) */
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        return -1;
    }

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count(); 
    srand(seed);




   

    /* Hook input callbacks */
    glfwSetKeyCallback(window, &key_callback);
    glfwSetMouseButtonCallback(window, &mouse_button_callback);
    glfwSetScrollCallback(window, &scroll_callback);
    glfwSetCursorPosCallback(window, &cursor_position_callback);
    glfwSetWindowSizeCallback(window, &size_callback);

    glimac::Program program = glimac::loadProgram(
    std::filesystem::current_path().string() + "/../../TP2/shaders/tex2D.vs.glsl",
    std::filesystem::current_path().string() + "/../../TP2/shaders/tex2D.fs.glsl");
    program.use();

    //recuperation de la variable uniforme
    // auto position = glGetUniformLocation(program.getGLId(), "uTime");
    auto position = glGetUniformLocation(program.getGLId(), "uModelMatrix");

    

    //cetait ça le truc pour le argv
    // glimac::FilePath applicationPath(argv[0]);
    // glimac::Program program = glimac::loadProgram(applicationPath.dirPath() + "TP2/shaders/"+argv[1], applicationPath.dirPath() + "TP2/shaders/"+ argv[2]);
    // program.use();






    // /*
    // * TRIANGLES
    // */
    // GLuint vbo;
    // glGenBuffers(1, &vbo);

    // glBindBuffer(GL_ARRAY_BUFFER, vbo);
    

    // std::vector<Vertex2DColor> vertices;
    // vertices.push_back(Vertex2DColor(glm::vec2(-0.5, -0.5), glm::vec3(1., 0., 0.)));
    // vertices.push_back(Vertex2DColor(glm::vec2(0.5, -0.5), glm::vec3(0., 1., 0.)));
    // vertices.push_back(Vertex2DColor(glm::vec2(0., 0.5), glm::vec3(0., 0., 1.)));

    
    // //envoi des coord
    // glBufferData(GL_ARRAY_BUFFER, 3*sizeof(Vertex2DColor), vertices.data(), GL_STATIC_DRAW);

    // //deBind du vbo pour eviter modif par erreur
    // glBindBuffer(GL_ARRAY_BUFFER, 0);



    // //specification des donnees pour expliquer a opengl comment gerer les objets en faisant un vao
    // GLuint vao;
    // glGenVertexArrays(1, &vao);

    // //bind du vao
    // glBindVertexArray(vao);


    // const GLuint VERTEX_ATTR_POSITION = 0;
    // glEnableVertexAttribArray(VERTEX_ATTR_POSITION);

    // const GLuint VERTEX_ATTR_COLOR = 1;
    // glEnableVertexAttribArray(VERTEX_ATTR_COLOR);

    // glBindBuffer(GL_ARRAY_BUFFER, vbo);    
    // glVertexAttribPointer(VERTEX_ATTR_POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2DColor), (const GLvoid*)offsetof(Vertex2DColor, m_position)); 

    // glVertexAttribPointer(VERTEX_ATTR_COLOR, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex2DColor), (const GLvoid*)offsetof(Vertex2DColor, m_color)); //position dans le vbo, la taille d'un attribut (nb coord), type, stride, taille d'asso de chaque coord (ici 5 * taille float), position du premier elem
    // glBindBuffer(GL_ARRAY_BUFFER, 0);

    // //debind de la vao
    // glBindVertexArray(0);







    // /*
    // * SQUARE 
    // */
    // GLuint vbo;
    // glGenBuffers(1, &vbo);

    // glBindBuffer(GL_ARRAY_BUFFER, vbo);
    

    // std::vector<Vertex2DColor> vertices;
    // vertices.push_back(Vertex2DColor(glm::vec2(-1., -1.)));
    // vertices.push_back(Vertex2DColor(glm::vec2(-1., 1.)));
    // vertices.push_back(Vertex2DColor(glm::vec2(1., 1.)));
    // vertices.push_back(Vertex2DColor(glm::vec2(-1., -1.)));
    // vertices.push_back(Vertex2DColor(glm::vec2(1., -1.)));
    // vertices.push_back(Vertex2DColor(glm::vec2(1., 1.)));

    
    // //envoi des coord
    // glBufferData(GL_ARRAY_BUFFER, 6*sizeof(Vertex2DColor), vertices.data(), GL_STATIC_DRAW);

    // //deBind du vbo pour eviter modif par erreur
    // glBindBuffer(GL_ARRAY_BUFFER, 0);



    // //specification des donnees pour expliquer a opengl comment gerer les objets en faisant un vao
    // GLuint vao;
    // glGenVertexArrays(1, &vao);

    // //bind du vao
    // glBindVertexArray(vao);


    // const GLuint VERTEX_ATTR_POSITION = 0;
    // glEnableVertexAttribArray(VERTEX_ATTR_POSITION);

    // const GLuint VERTEX_ATTR_COLOR = 1;
    // glEnableVertexAttribArray(VERTEX_ATTR_COLOR);

    // glBindBuffer(GL_ARRAY_BUFFER, vbo);    
    // glVertexAttribPointer(VERTEX_ATTR_POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2DColor), (const GLvoid*)offsetof(Vertex2DColor, m_position)); 

    // glVertexAttribPointer(VERTEX_ATTR_COLOR, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex2DColor), (const GLvoid*)offsetof(Vertex2DColor, m_color)); //position dans le vbo, la taille d'un attribut (nb coord), type, stride, taille d'asso de chaque coord (ici 5 * taille float), position du premier elem
    // glBindBuffer(GL_ARRAY_BUFFER, 0);

    // //debind de la vao
    // glBindVertexArray(0);


    GLuint vbo;
    glGenBuffers(1, &vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    std::vector<Vertex2DUV> vertices;
    vertices.push_back(Vertex2DUV(glm::vec2(-1., -1.), glm::vec2(0., 0.)));
    vertices.push_back(Vertex2DUV(glm::vec2(1., -1.), glm::vec2(0., 0.)));
    vertices.push_back(Vertex2DUV(glm::vec2(0., 1.), glm::vec2(0., 0.)));

    glBufferData(GL_ARRAY_BUFFER, 3*sizeof(Vertex2DUV), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLuint vao;

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    const GLuint VERTEX_ATTR_POSITION = 0;
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);

    const GLuint VERTEX_ATTR_COLOR = 1;
    glEnableVertexAttribArray(VERTEX_ATTR_COLOR);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);    
    glVertexAttribPointer(VERTEX_ATTR_POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2DUV), (const GLvoid*)offsetof(Vertex2DUV, m_position)); 

    glVertexAttribPointer(VERTEX_ATTR_COLOR, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2DUV), (const GLvoid*)offsetof(Vertex2DUV, m_texture)); //position dans le vbo, la taille d'un attribut (nb coord), type, stride, taille d'asso de chaque coord (ici 5 * taille float), position du premier elem
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //debind de la vao
    glBindVertexArray(0);



    auto start = std::chrono::steady_clock::now();

    
       
	









    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {


        glClearColor(0.f, 0.0f, 0.0f, 1.f);

        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = end-start; 

        glm::mat3 mat_rot = rotate(elapsed_seconds.count());
        glUniformMatrix3fv(position,1,GL_FALSE, glm::value_ptr(mat_rot));

        // /*
        // * TRIANGLE
        // */
        // glClear(GL_COLOR_BUFFER_BIT);
        // glBindVertexArray(vao);
        // glDrawArrays(GL_TRIANGLES,0,3);
        // glBindVertexArray(0);

        // /*
        // * SQUARE
        // */
        // glClear(GL_COLOR_BUFFER_BIT);
        // glBindVertexArray(vao);
        // glDrawArrays(GL_TRIANGLES,0,3);
        // glBindVertexArray(0);

        /*
        * TRIANGLE QUI rotation
        */

        // glUniform1f(position, rotation);
        // rotation+=5;

        glClear(GL_COLOR_BUFFER_BIT);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES,0,3);
        glBindVertexArray(0);


        



        glfwSwapBuffers(window);
        glfwPollEvents();

        
    }


    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);


    glfwTerminate();
    return 0;
}
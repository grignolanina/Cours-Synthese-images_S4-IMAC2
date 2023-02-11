#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>

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

// int main(int argc, char const *argv[])
int main()
{
    /* Initialize the library */
    if (!glfwInit()) {
        return -1;
    }

    // //ex2
    // glimac::FilePath applicationPath(argv[0]);
    // glimac::Program program = glimac::loadProgram(applicationPath.dirPath() + "shaders/triangle.vs.glsl", applicationPath.dirPath() + "shaders/triangle.fs.glsl");
    // program.use();

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

    /* Hook input callbacks */
    glfwSetKeyCallback(window, &key_callback);
    glfwSetMouseButtonCallback(window, &mouse_button_callback);
    glfwSetScrollCallback(window, &scroll_callback);
    glfwSetCursorPosCallback(window, &cursor_position_callback);
    glfwSetWindowSizeCallback(window, &size_callback);

    /*
     *         EXO1
    */

    //___________INITIALISATION
    //Creation d'un seul VBO
    GLuint vbo;
    glGenBuffers(1, &vbo);

    // //Creation de plusieurs VBO
    // GLuint vbos[16];
    // glGenBuffers(16,vbos);


    //Bind(lien) du vbo sur la cible GL_ARRAY_BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    //-> cela permet de pouvoir directement modifier le vbo en passant pas la cible GL_ARRAY_BUFFER


    //crea des donnees pour notre triangle
    //coord
    GLfloat vertices[] ={-0.5f, -0.5f, 0.5f, -0.5f, 0.0f, 0.5f};
    //envoi des coord
    glBufferData(GL_ARRAY_BUFFER, 6*sizeof(GLfloat), vertices, GL_STATIC_DRAW);

    //deBind du vbo pour eviter modif par erreur
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //specification des donnees pour expliquer a opengl comment gerer les objets en faisant un vao
    GLuint vao;
    glGenVertexArrays(1, &vao);

    //bind du vao
    glBindVertexArray(vao);

    //pour indiquer au tableau les attributs que l'on utilise
    //position a,pour id l entier 0 (change avec buffer) pour que ce soit plus clair on cree des variables (VERTEX_ATTR_POSITION)
    ///!\ a bien avoir bind avant sinon erreur compliquer a gerer
    const GLuint VERTEX_ATTR_POSITION = 0;
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);

    //pour aider opengl a comprendre comment lire les sommets
    //pour que opengl sache vbo il doit utiliser il faut le bind juste avant et le debind juste apres
    glBindBuffer(GL_ARRAY_BUFFER, vbo);    
    glVertexAttribPointer(VERTEX_ATTR_POSITION, 2, GL_FLOAT, GL_FALSE, 2 *sizeof(GLfloat), 0); //position dans le vbo, la taille d'un attribut (nb coord), type, stride, taille d'asso de chaque coord (ici 2 * taille float), position du premier elem
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //debind de la vao
    glBindVertexArray(0);





    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        glClearColor(1.f, 0.5f, 0.5f, 1.f);

        /*
        *         EXO1
        */
        //___________DESSIN
        // //pour nettoyer les residus dans la fenetre
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES,0,3); //on dessine des triangles, en partant du 0, ils ont tous 3 sommets
        glBindVertexArray(0);


        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        /* Poll for and process events */
        glfwPollEvents();

        
    }

    /*
     *         EXO1
    */
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);


    glfwTerminate();
    return 0;
}
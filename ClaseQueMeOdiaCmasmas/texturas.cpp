#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void recursive(glm::vec3 mycolor, glm::mat4 transform, Shader nuestroShader, unsigned int transformLoc, unsigned int VAO, int triangles);
//nuestras configuraciones
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera

float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

int main()
{
    //inicializamos glfw
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //Creacion de nuestra ventanita hermosa bella de chula
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "tortita", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "fallaste, mejor llora XD" << std::endl;
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    //comprobamos nuestro alegre
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "oye wey no se esta ejecutando el alegre" << std::endl;
        return -1;
    }

    //Declarar nuestro programa shader y sus compilaciones
    Shader nuestroShader("texturas.vs", "texturas2.vs");
    Shader nuestroShader2("texturas.vs", "texturas2.vs");

    //declaramos nuestros vertices con sus atributos

    float vertices[] = {
        0.15f,  0.1f, 0.0f,   1.0f, 1.0f, 1.0f,  1.0f, 1.0f, //derecha superior 0
        0.15f, -0.1f, 0.0f,  1.0f, 1.0f, 1.0f,  1.0f, 0.0f, //derecha inferior 1
         -0.15f, -0.1f, 0.0f,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f, //izquierda inferior 2
        -0.15f,  0.1f, 0.0f,   1.0f, 1.0f, 1.0f,  0.0f, 1.0f,  //izquierda superior 3

           0.1f,  0.1f, 0.0f,   1.0f, 1.0f, 1.0f,  0.0f, 0.0f, //derecha superior 0
        0.1f, -0.1f, 0.0f,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f, //derecha inferior 1
         -0.1f, -0.1f, 0.0f,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f, //izquierda inferior 2
        -0.1f,  0.1f, 0.0f,   1.0f, 1.0f, 1.0f,  0.0f, 0.0f
        /*-1.0f,  0.5f, 0.0f,   1.0f, 1.0f, 1.0f,  1.0f, 1.0f, //derecha superior 0
         -0.8f, -0.5f, 0.0f,  1.0f, 1.0f, 1.0f,  1.0f, 0.0f, //derecha inferior 1
         -0.8f, -0.2f, 0.0f,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f, //izquierda inferior 2
        -0.9f,  0.6f, 0.0f,   1.0f, 1.0f, 1.0f,  0.0f, 1.0f,  //izquierda superior 3

        -0.8f,  -0.5f, 0.0f,  1.0f, 1.0f, 1.0f,  1.0f, 1.0f, //derecha superior 0
        -0.8f, -0.2f, 0.0f,   1.0f, 1.0f, 1.0f,  1.0f, 0.0f, //derecha inferior 1
        -0.6f, 0.6f, 0.0f,    1.0f, 1.0f, 1.0f,  0.0f, 0.0f, //izquierda inferior 2
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 1.0f,  0.0f, 1.0f,  //izq
         /// PRIMERA H
        -0.45f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,  0.0f, 0.0f, //derecha superior 0
        -0.45f, -0.5f, 0.0f,  1.0f, 0.5f, 0.0f,  0.0f, 0.0f, //derecha inferior 1
        -0.35f,  -0.5f, 0.0f,   1.0f, 1.0f, 0.0f,  0.0f, 0.0f, //izquierda inferior 2
        -0.35f, 0.5f, 0.0f,  1.0f, 1.0f, 0.0f,  0.0f, 0.0f,  //izq


        -0.25f,  0.5f, 0.0f,  1.0f, 1.0f, 0.0f,  0.0f, 0.0f, //derecha superior 0
        -0.25f, -0.5f, 0.0f,  1.0f, 0.5f, 0.0f,  0.0f, 0.0f, //derecha inferior 1
        -0.15f,  -0.5f, 0.0f,  1.0f, 1.0f, 0.8f,  0.0f, 0.0f, //izquierda inferior 2
        -0.15f, 0.5f, 0.0f,  1.0f, 1.0f, 0.0f,  0.0f, 0.0f,  //izq


        -0.45f,  0.1f, 0.0f,  1.0f, 1.0f, 0.0f,  0.0f, 0.0f, //derecha superior 0
        -0.45f, -0.1f, 0.0f,  1.0f, 0.5f, 0.0f,  0.0f, 0.0f, //derecha inferior 1
        -0.15f, -0.1f, 0.0f,  1.0f, 1.0f, 0.8f,  0.0f, 0.0f, //izquierda inferior 2
        -0.15f,  0.1f, 0.0f,  1.0f, 1.0f, 0.0f,  0.0f, 0.0f,  //izq

        //asjidasfnasdfjkadsfj
        -0.05f,  0.5f, 0.0f,  1.0f, 1.0f, 0.0f,  0.0f, 0.0f, //derecha superior 0
        -0.05f, -0.5f, 0.0f,  1.0f, 0.5f, 0.0f,  0.0f, 0.0f, //derecha inferior 1
         0.05f, -0.5f, 0.0f,  1.0f, 1.0f, 0.8f,  0.0f, 0.0f, //izquierda inferior 2
         0.05f,  0.5f, 0.0f,  1.0f, 1.0f, 0.0f,  0.0f, 0.0f,  //izq


        0.15f,  0.5f, 0.0f,  1.0f, 1.0f, 0.0f,  0.0f, 0.0f, //derecha superior 0
        0.15f, -0.5f, 0.0f,  1.0f, 0.5f, 0.0f,  0.0f, 0.0f, //derecha inferior 1
        0.25f,  -0.5f, 0.0f,  1.0f, 1.0f, 0.8f,  0.0f, 0.0f, //izquierda inferior 2
        0.25f, 0.5f, 0.0f,  1.0f, 1.0f, 0.0f,  0.0f, 0.0f,  //izq


        -0.05f,  0.1f, 0.0f,  1.0f, 1.0f, 0.0f,  0.0f, 0.0f, //derecha superior 0
        -0.05f, -0.1f, 0.0f,  1.0f, 0.5f, 0.0f,  0.0f, 0.0f, //derecha inferior 1
         0.25f, -0.1f, 0.0f,  1.0f, 1.0f, 0.8f,  0.0f, 0.0f, //izquierda inferior 2
         0.25f,  0.1f, 0.0f,  1.0f, 1.0f, 0.0f,  0.0f, 0.0f, //izq

         //xvsdfsd
          0.5f,  0.0f, 0.0f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f, //derecha superior 0
         0.5f, -0.2f, 0.0f,  0.0f, 0.5f, 0.0f,  0.0f, 0.0f, //derecha inferior 1
         0.8f, -0.2f, 0.0f,  0.0f, 0.0f, 0.8f,  0.0f, 0.0f, //izquierda inferior 2
         0.8f,  0.0f, 0.0f,  1.0f, 1.0f, 0.0f,  0.0f, 0.0f,
         
         0.3f,  -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f, //derecha superior 0
         0.7f, 0.7f, 0.0f,  0.0f, 0.5f, 0.0f,  0.0f, 0.0f, //derecha inferior 1
         0.65f, 0.2f, 0.0f,  0.0f, 0.0f, 0.8f,  0.0f, 0.0f, //izquierda inferior 2
         0.5f,  -0.6f, 0.0f,  1.0f, 1.0f, 0.0f,  0.0f, 0.0f,  //izquierda superior 3

         0.8f,  -0.6f, 0.0f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f, //derecha superior 0
         0.65f, 0.2f, 0.0f,  0.0f, 0.5f, 0.0f,  0.0f, 0.0f, //derecha inferior 1
         0.7f, 0.7f, 0.0f,  0.0f, 0.0f, 0.8f,  0.0f, 0.0f, //izquierda inferior 2
         1.0f,  -0.5f, 0.0f,  1.0f, 1.0f, 0.0f,  0.0f, 0.0f,  //izq
         */
        
    };

    float vertices2[] = {
        0.15f,  0.1f, 0.0f,   1.0f, 1.0f, 1.0f,  1.0f, 1.0f, //derecha superior 0
        0.15f, -0.1f, 0.0f,  1.0f, 1.0f, 1.0f,  1.0f, 0.0f, //derecha inferior 1
         -0.15f, -0.1f, 0.0f,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f, //izquierda inferior 2
        -0.15f,  0.1f, 0.0f,   1.0f, 1.0f, 1.0f,  0.0f, 1.0f,  //izquierda superior 3

    };

    unsigned int indices2[]{
        0,3,2,
        0,2,1,
        4,7,6,
        4,6,5,
        
        8, 11, 10,
        8, 10, 9,

        12, 15, 14,
        12, 14, 13,

        16, 19, 18,
        16, 18, 17,
        //qweqrw
        20, 23, 22,
        20, 22, 21,

        24, 27, 26,
        24, 26, 25,

        28, 31, 30,
        28, 30, 29,

        32, 35, 34,
        32, 34, 33,

        36, 39, 38,
        36, 38, 37,

        40, 43,42,
        40, 42, 41,

        44, 47, 46,
        44, 46, 45,

        48,51,50,
        48,50,49,

        52,55,54,
        52,54,53,

        56,59,58,
        56,58,57,

        60,63,62,
        60,62,61,

        64,67,66,
        64,66,65,

        68,71,70,
        68,70,69,

        72,75,74,
        72,74,73,

        76,79,78,
        76,78,77,

        80,83,82,
        80,82,81,

        84,87,85,
        84,85,86,

        88,91,89,
        88,89,90,

        92,95,94,
        92,94,93,

        96,99,98,
        96,98,97,

        100,103,102,
        100,102,101
    };
    unsigned int indices[]{
        0, 3, 2, //primer triangulo
        0, 2, 1, //segundo triangulo
        
        4, 7, 6,
        4, 6, 5,
        //qweqweq
        8, 11, 10,
        8, 10, 9,

        12, 15, 14,
        12, 14, 13,

        16, 19, 18,
        16, 18, 17,
        //qweqrw
        20, 23, 22,
        20, 22, 21,
        
        24, 27, 26,
        24, 26, 25,

        28, 31, 30,
        28, 30, 29,

        32, 35, 34,
        32, 34, 33,

        36, 39, 38,
        36, 38, 37,
        
        40, 43,42,
        40, 42, 41,

        44, 47, 46,
        44, 46, 45,

        48,51,50,
        48,50,49,

        52,55,54,
        52,54,53,

        56,59,58,
        56,58,57,

        60,63,62,
        60,62,61,

        64,67,66,
        64,66,65,

        68,71,70,
        68,70,69,
        
        72,75,74,
        72,74,73,

        76,79,78,
        76,78,77,

        80,83,82,
        80,82,81,

        84,87,85,
        84,85,86,

        88,91,89,
        88,89,90,

        92,95,94,
        92,94,93,

        96,99,98,
        96,98,97,

        100,103,102,
        100,102,101
    };

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    //unificar 
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //atributos de posicion 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //atributos de color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    //atributos de nuestras texturas
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);


    unsigned int VBO2, VAO2, EBO2;
    glGenVertexArrays(1, &VAO2);
    glGenBuffers(1, &VBO2);
    glGenBuffers(1, &EBO2);
    //unificar 
    glBindVertexArray(VAO2);

    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO2);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices2), indices2, GL_STATIC_DRAW);

    //atributos de posicion 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //atributos de color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    //atributos de nuestras texturas
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);



    //creamos y cargamos las texturas
    //-------------------------------
    unsigned int textura1, textura2,textura3;
    //configurar nuestra primera textura
    glGenTextures(1, &textura1);
    glBindTexture(GL_TEXTURE_2D, textura1);
    //configurar como queremos que actue nuestra mascara de textura en nuestro objeto
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //X
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); //Y
    //Configuramos el tipo de filtrado que va a manejar nuestra textura
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    //Cargar nuestra textura
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(("dd.jpg"), &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "fallaste en cargar la primera textura" << std::endl;
    }
    stbi_image_free(data);

    //Textura 2
    glGenTextures(1, &textura2);
    glBindTexture(GL_TEXTURE_2D, textura2);
    //configurar como queremos que actue nuestra mascara de textura en nuestro objeto
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //X
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); //Y
    //Configuramos el tipo de filtrado que va a manejar nuestra textura
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    //Cargar nuestra textura
    data = stbi_load(("dvd.png"), &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "fallaste en cargar la segunda textura" << std::endl;
    }
    stbi_image_free(data);

    //Textura 2
    glGenTextures(1, &textura3);
    glBindTexture(GL_TEXTURE_2D, textura3);
    //configurar como queremos que actue nuestra mascara de textura en nuestro objeto
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //X
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); //Y
    //Configuramos el tipo de filtrado que va a manejar nuestra textura
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    //Cargar nuestra textura
    data = stbi_load(("pp.png"), &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "fallaste en cargar la segunda textura" << std::endl;
    }
    stbi_image_free(data);


    //empezamos a utilizar nuestra libreria shader
    nuestroShader.use();
    
    //glUniform1i(glGetUniformLocation(nuestroShader.ID, "textura1"), 0);



    glm::vec3 c1 = glm::vec3(-0.2f, -1.0f, 0.0f);
    glm::vec3 c2 = glm::vec3(1.0f, 0.8f, 0.0f);

    glm::vec3 c3 = glm::vec3(0.8f, 1.0f, 0.0f);
    glm::vec3 c4 = glm::vec3(-1.0f, -0.8f, 0.0f);
    //loop de dibujado

    float time = 0.0001f;
    float nextInterpolation = 0.0f;
    int pos = 1;

    while (!glfwWindowShouldClose(window))
    {
        //entradas
        processInput(window);

        //renderizado
        glClearColor(cos(glfwGetTime()) * 0.5f, sin(glfwGetTime()) * 0.2f, sin(glfwGetTime()), 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        

        nuestroShader.setInt("textura1", 0);

        nuestroShader.setInt("textura2", 1);
        //unificar nuestras texturas y activarlas
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textura1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, textura2);
  
       


        glm::mat4 model = glm::mat4(1.0f);
       glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);
       /* model = glm::rotate(model, glm::radians(-50.0f), glm::vec3(1.0f,0.0f,0.0f));
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        projection = glm::perspective(glm::radians(45.0f),(float)SCR_WIDTH / (float) SCR_HEIGHT,0.1f,100.0f);
        */
        nuestroShader.use();
        unsigned int modelLoc = glGetUniformLocation(nuestroShader.ID, "model");
        unsigned int viewLoc = glGetUniformLocation(nuestroShader.ID, "view");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);

        nuestroShader.setMat4("projection", projection);


        



        glm::mat4 transform = glm::mat4(1.0f);
        glm::vec3 mycolor = glm::vec3(0.5f, 0.5f, 0.5f);
        nextInterpolation += glfwGetTime() * time;

        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
      /*
        switch (pos)
        {
        case 1:
           transform = glm::translate(transform, glm::mix(c1, c2, glfwGetTime() * 0.10f));
           if (nextInterpolation > 7.25f)
           {
               pos++;
               nextInterpolation = 0;
               glfwSetTime(0);
           }
          
            nuestroShader.use();
            mycolor = glm::vec3(0.5f, 0.5f, 0.0f);
            //nuestroShader.setVec3("color", glm::vec3(0.5f, 0.5f, 0.5f));
            break;
        case 2:
            transform = glm::translate(transform, glm::mix(c2, c3, glfwGetTime() * 0.30f));
            if (nextInterpolation > 1.0f)
            {
                pos++;
                nextInterpolation = 0;
                glfwSetTime(0);
            }
            mycolor = glm::vec3(0.5f, 0.0f, 0.5f);
            nuestroShader.use();
            break;
        case 3:
            transform = glm::translate(transform, glm::mix(c3, c4, glfwGetTime() * 0.10f));
            if (nextInterpolation > 8.0f)
            {
                pos++;
                nextInterpolation = 0;
                glfwSetTime(0);
            }
            mycolor = glm::vec3(0.0f, 0.5f, 0.5f);
            nuestroShader.use();
            break;
        case 4:
            transform = glm::translate(transform, glm::mix(c4, c1, glfwGetTime() * 0.10f));
            nuestroShader.use();
            pos = 1;
            if (nextInterpolation > 1.0f)
            {
                pos++;
                nextInterpolation = 0;
                glfwSetTime(0);
            }
            mycolor = glm::vec3(0.5f, 0.5f, 0.5f);
            std::cout << "fallaste " + pos << std::endl;
            break;
        default:
            break;
        }
        //glm::vec3 newPos = lerp(c1, c2, 2.0f);
   
   */
         // make sure to initialize matrix to identity matrix first
       // transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
        //transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

        //nuestroShader.use();
        //transform = glm::translate(transform, c1);
 
        //transform = glm::translate(transform, c2);
        //nuestroShader.use();
        //transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
        //float scaleAmount = cos(glfwGetTime());
        //transform = glm::scale(transform, glm::vec3(1.0f, 1.0f, 1.0f));
    
       /*
        transform = glm::translate(transform, glm::mix(c3, c4, glfwGetTime() * 0.2f));
        //transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
       scaleAmount = sin(glfwGetTime());
        transform = glm::scale(transform, glm::vec3(1.0f, 1.0f, 1.0f));
        nuestroShader.use();
        
      
        nuestroShader.use();

        transform = glm::translate(transform, glm::mix(c1, c2, glfwGetTime() * 0.2f));
        //transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
        //float scaleAmount = cos(glfwGetTime());
        //transform = glm::scale(transform, glm::vec3(1.0f, 1.0f, 1.0f));
        nuestroShader.use();*/
       /*nuestroShader.setVec3("color", mycolor);
       unsigned int transformLoc = glGetUniformLocation(nuestroShader.ID, "transform");
       glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
       */
        unsigned int transformLoc = 0;
        //recursive(mycolor, transform, nuestroShader, transformLoc,VAO, 6);
       
      // glBindVertexArray(VAO);
       //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        float scaleAmount = cos(glfwGetTime());
      
        nuestroShader.use();

        nuestroShader.use();
      
        for (int x = 0; x < 10 ;x++)
        {
            transform = glm::translate(transform, glm::mix(glm::vec3(-0.0f, x/10, 0.0), glm::vec3(1.0f, x/10, 0.0f), cos(glfwGetTime()) * 0.5f));
            mycolor = glm::vec3(0.5f, 0.5f, 0.5f);
            recursive(mycolor, transform, nuestroShader, transformLoc, VAO, 6);
        }

        nuestroShader.use();
        for (float x = 0; x < 2; x++)
        {
            transform = glm::translate(transform, glm::mix(glm::vec3(x/10, -0.0f, 0.0), glm::vec3(1.0f, 0.5f, 0.0f), sin(glfwGetTime()) * 0.5f));
            mycolor = glm::vec3(0.5f, 0.5f, 0.5f);
            recursive(mycolor, transform, nuestroShader, transformLoc, VAO, 6);
        }

        nuestroShader.use();

            transform = glm::translate(transform, glm::vec3(0.5f,0.8f,0.0f));
            mycolor = glm::vec3(scaleAmount, scaleAmount,scaleAmount);
            recursive(mycolor, transform, nuestroShader, transformLoc, VAO, 6);
        
            nuestroShader.use();

       //nuestroShader.use();
      /* transform = glm::translate(transform, glm::mix(glm::vec3(-0.0f, 0.5f, 0.0), glm::vec3(1.0f, 0.5f, 0.0f), cos(glfwGetTime()) * 0.5f));
       mycolor = glm::vec3(1.0f, 1.0f, 1.0f);
       recursive(mycolor, transform, nuestroShader, transformLoc, VAO,6);
       */


      nuestroShader2.use();
      nuestroShader2.setInt("textura1", 0);

      nuestroShader2.setInt("textura3", 1);
      glActiveTexture(GL_TEXTURE0);
      glBindTexture(GL_TEXTURE_2D, textura1);
      glActiveTexture(GL_TEXTURE1);
      glBindTexture(GL_TEXTURE_2D, textura3);
      
      glm::mat4 model2 = glm::mat4(1.0f);
      glm::mat4 view2 = glm::mat4(1.0f);
      glm::mat4 projection2 = glm::mat4(1.0f);
      glm::mat4 transform2 = glm::mat4(1.0f);
      glm::vec3 mycolor2 = glm::vec3(0.5f, 0.5f, 0.5f);
      unsigned int transformLoc2 = 0;
      nuestroShader2.use();
      unsigned int modelLoc2 = glGetUniformLocation(nuestroShader2.ID, "model");
      unsigned int viewLoc2 = glGetUniformLocation(nuestroShader2.ID, "view");
      glUniformMatrix4fv(modelLoc2, 1, GL_FALSE, glm::value_ptr(model2));
      glUniformMatrix4fv(viewLoc2, 1, GL_FALSE, &view2[0][0]);

      nuestroShader2.setMat4("projection", projection2);
      transform2 = glm::translate(transform2, glm::vec3(-0.9f, 0.9f, 0.0f));
      transform2 = glm::rotate(transform2, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
      recursive(mycolor2, transform2, nuestroShader2, transformLoc2, VAO2, 6);
     
      transform2 = glm::translate(transform2, glm::vec3(-1.9f, 0.0f, 0.0f));
      transform2 = glm::rotate(transform2, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
      recursive(mycolor2, transform2, nuestroShader2, transformLoc2, VAO2, 6);




      glm::mat4 model3 = glm::mat4(1.0f);
      glm::mat4 view3 = glm::mat4(1.0f);
      glm::mat4 projection3 = glm::mat4(1.0f);
      glm::mat4 transform3 = glm::mat4(1.0f);
      glm::vec3 mycolor3 = glm::vec3(0.5f, 0.5f, 0.5f);
      unsigned int transformLoc3 = 0;
      nuestroShader2.use();
      unsigned int modelLoc3 = glGetUniformLocation(nuestroShader2.ID, "model");
      unsigned int viewLoc3 = glGetUniformLocation(nuestroShader2.ID, "view");
      glUniformMatrix4fv(modelLoc3, 1, GL_FALSE, glm::value_ptr(model3));
      glUniformMatrix4fv(viewLoc3, 1, GL_FALSE, &view3[0][0]);

      nuestroShader2.setMat4("projection", projection3);

      transform3 = glm::translate(transform2, glm::vec3(-0.9f, -0.9f, 0.0f));
      transform3 = glm::rotate(transform2, (float)glfwGetTime(), glm::vec3(0.9f, 0.9f, 0.0f));
      recursive(mycolor2, transform2, nuestroShader2, transformLoc3, VAO2, 6);

      transform3 = glm::translate(transform3, glm::vec3(-1.9f, 0.0f, 0.0f));
      transform3 = glm::rotate(transform3, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
      recursive(mycolor3, transform3, nuestroShader2, transformLoc3, VAO2, 6);



      glm::mat4 model4 = glm::mat4(1.0f);
      glm::mat4 view4 = glm::mat4(1.0f);
      glm::mat4 projection4 = glm::mat4(1.0f);
      glm::mat4 transform4 = glm::mat4(1.0f);
      glm::vec3 mycolor4 = glm::vec3(0.5f, 0.5f, 0.5f);
      unsigned int transformLoc4 = 0;
      nuestroShader2.use();
      unsigned int modelLoc4 = glGetUniformLocation(nuestroShader2.ID, "model");
      unsigned int viewLoc4 = glGetUniformLocation(nuestroShader2.ID, "view");
      glUniformMatrix4fv(modelLoc4, 1, GL_FALSE, glm::value_ptr(model4));
      glUniformMatrix4fv(viewLoc4, 1, GL_FALSE, &view4[0][0]);

      nuestroShader2.setMat4("projection", projection4);
      transform4 = glm::translate(transform4, glm::vec3(-0.9f, -0.9f, 0.0f));
      transform4 = glm::rotate(transform4, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
      recursive(mycolor4, transform4, nuestroShader2, transformLoc4, VAO2, 6);

      transform4 = glm::translate(transform4, glm::vec3(-1.9f, 0.0f, 0.0f));
      transform4 = glm::rotate(transform4, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
      recursive(mycolor4, transform4, nuestroShader2, transformLoc4, VAO2, 6);

      glm::mat4 model5 = glm::mat4(1.0f);
      glm::mat4 view5 = glm::mat4(1.0f);
      glm::mat4 projection5 = glm::mat4(1.0f);
      glm::mat4 transform5 = glm::mat4(1.0f);
      glm::vec3 mycolor5 = glm::vec3(0.5f, 0.5f, 0.5f);
      unsigned int transformLoc5 = 0;
      nuestroShader.use();
      unsigned int modelLoc5 = glGetUniformLocation(nuestroShader.ID, "model");
      unsigned int viewLoc5 = glGetUniformLocation(nuestroShader.ID, "view");
      glUniformMatrix4fv(modelLoc5, 1, GL_FALSE, glm::value_ptr(model5));
      glUniformMatrix4fv(viewLoc5, 1, GL_FALSE, &view5[0][0]);
      nuestroShader.setMat4("projection", projection5);

      nuestroShader.use();

      for (int x = 0; x < 10; x++)
      {
          transform5 = glm::translate(transform5, glm::mix(glm::vec3( x / 10, 0.0f, 0.0), glm::vec3( x / 10,1.0f, 0.0f), cos(glfwGetTime()) * 0.5f));
          mycolor5 = glm::vec3(0.5f, 0.5f, 0.5f);
          recursive(mycolor5, transform5, nuestroShader, transformLoc5, VAO, 6);
      }

      nuestroShader.use();
      for (float x = 0; x < 2; x++)
      {
          transform5 = glm::translate(transform5, glm::mix(glm::vec3( -0.0f, x/10, 0.0), glm::vec3(0.5f, 1.0f, 0.0f), sin(glfwGetTime()) * 0.5f));
          mycolor5 = glm::vec3(0.5f, 0.5f, 0.5f);
          recursive(mycolor5, transform5, nuestroShader, transformLoc5, VAO, 6);
      }

      nuestroShader.use();

      transform5 = glm::translate(transform5, glm::vec3(0.8f, 0.5f, 0.0f));
      mycolor5 = glm::vec3(scaleAmount, scaleAmount, scaleAmount);
      recursive(mycolor5, transform5, nuestroShader, transformLoc5, VAO, 6);

      nuestroShader.use();


       glfwSwapBuffers(window);
       glfwPollEvents();
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glDeleteVertexArrays(1, &VAO2);
    glDeleteBuffers(1, &VBO2);
    glDeleteBuffers(1, &EBO2);

    glfwTerminate();
    return 0;


}

void recursive(glm::vec3 mycolor, glm::mat4 transform,Shader nuestroShader, unsigned int transformLoc,unsigned int VAO, int triangles)
{
    nuestroShader.setVec3("color", mycolor);
    transformLoc = glGetUniformLocation(nuestroShader.ID, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, triangles, GL_UNSIGNED_INT, 0);

}

glm::vec3 lerp(glm::vec3 x, glm::vec3 y, float t) {
    return x * (1.f - t) + y * t;
}


glm::vec3 modelPosition(glm::vec3 A, glm::vec3 B, glm::vec3 C, float t) {
    if (t < 0.0) {
        return A;
    }
    else if (t < 1.0) {
        return lerp(A, B, t);
    }
    else if (t < 2.0) {
        return lerp(B, C, t - 1.0);
    }
    else {
        return C;
    }
}
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
   glViewport(0, 0, width, height);
}


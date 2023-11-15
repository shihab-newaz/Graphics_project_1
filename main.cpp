#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "camera.h"
#include "basic_camera.h"
#include "pointLight.h"
#include "directionalLight.h"
#include "sphere.h"
#include "spotLight.h"
#include "cube.h"
#include "stb_image.h"
#include <iostream>
#include <vector>


using namespace std;

//prototype declarations
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
void drawCube(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 model, float r, float g, float b);
void drawCurve(unsigned int& bezierVAO, Shader& lightingShader, glm::mat4 model = glm::mat4(1.0f), float r = 1.0f, float g = 1.0f, float b = 1.0f);

void chess_board(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether);
void cube_1(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether, float x, float y, float z,
    float cube_height, float cube_w, float cube_b, float r, float g, float b);

void drawSphere(Shader& lightingShader, glm::mat4 alTogether, float x, float y, float z, float h, float w, float b, float red, float green, float blue);


void clock1(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether);
void bishop1(unsigned int& bezierVAO, unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether, float x, float y, float z, float h, float w, 
    float b,  float r, float g, float bl, float cube_x, float cube_y, float cube_z);
void bishop2(unsigned int& bezierVAO, unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether, float x, float y, float z, float h, float w,
    float b, float r, float g, float bl, float cube_x, float cube_y, float cube_z);
void bishop3(unsigned int& bezierVAO, unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether, float x, float y, float z, float h, float w,
    float b, float r, float g, float bl, float cube_x, float cube_y, float cube_z);
void bishop4(unsigned int& bezierVAO, unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether, float x, float y, float z, float h, float w,
    float b, float r, float g, float bl, float cube_x, float cube_y, float cube_z);
void pawn1(unsigned int& bezierVAO,unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether, float cube_x, float cube_y, float cube_z,
    float cube_height, float cube_w, float cube_b, float sphere_x, float sphere_y, float sphere_z, float sphere_height, float sphere_w,
    float sphere_b, float r, float g, float b);
void pawn2(unsigned int& bezierVAO,unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether, float cube_x, float cube_y, float cube_z,
    float cube_height, float cube_w, float cube_b, float sphere_x, float sphere_y, float sphere_z, float sphere_height, float sphere_w,
    float sphere_b, float r, float g, float b);
void pawn3(unsigned int& bezierVAO, unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether, float cube_x, float cube_y, float cube_z,
    float cube_height, float cube_w, float cube_b, float sphere_x, float sphere_y, float sphere_z, float sphere_height, float sphere_w,
    float sphere_b, float r, float g, float b);
void pawn4(unsigned int& bezierVAO, unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether, float cube_x, float cube_y, float cube_z,
    float cube_height, float cube_w, float cube_b, float sphere_x, float sphere_y, float sphere_z, float sphere_height, float sphere_w,
    float sphere_b, float r, float g, float b);
void pawn5(unsigned int& bezierVAO, unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether, float cube_x, float cube_y, float cube_z,
    float cube_height, float cube_w, float cube_b, float sphere_x, float sphere_y, float sphere_z, float sphere_height, float sphere_w,
    float sphere_b, float r, float g, float b);
void pawn6(unsigned int& bezierVAO, unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether, float cube_x, float cube_y, float cube_z,
    float cube_height, float cube_w, float cube_b, float sphere_x, float sphere_y, float sphere_z, float sphere_height, float sphere_w,
    float sphere_b, float r, float g, float b);
void pawn7(unsigned int& bezierVAO, unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether, float cube_x, float cube_y, float cube_z,
    float cube_height, float cube_w, float cube_b, float sphere_x, float sphere_y, float sphere_z, float sphere_height, float sphere_w,
    float sphere_b, float r, float g, float b);
void pawn8(unsigned int& bezierVAO, unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether, float cube_x, float cube_y, float cube_z,
    float cube_height, float cube_w, float cube_b, float sphere_x, float sphere_y, float sphere_z, float sphere_height, float sphere_w,
    float sphere_b, float r, float g, float b);
void pawn9(unsigned int& bezierVAO, unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether, float cube_x, float cube_y, float cube_z,
    float cube_height, float cube_w, float cube_b, float sphere_x, float sphere_y, float sphere_z, float sphere_height, float sphere_w,
    float sphere_b, float r, float g, float b);
void pawn10(unsigned int& bezierVAO, unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether, float cube_x, float cube_y, float cube_z,
    float cube_height, float cube_w, float cube_b, float sphere_x, float sphere_y, float sphere_z, float sphere_height, float sphere_w,
    float sphere_b, float r, float g, float b);
void pawn11(unsigned int& bezierVAO, unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether, float cube_x, float cube_y, float cube_z,
    float cube_height, float cube_w, float cube_b, float sphere_x, float sphere_y, float sphere_z, float sphere_height, float sphere_w,
    float sphere_b, float r, float g, float b);
void pawn12(unsigned int& bezierVAO, unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether, float cube_x, float cube_y, float cube_z,
    float cube_height, float cube_w, float cube_b, float sphere_x, float sphere_y, float sphere_z, float sphere_height, float sphere_w,
    float sphere_b, float r, float g, float b);
void queen1(unsigned int& bezierVAO, unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether, float x, float y, float z, float h, 
    float w, float b,  float r, float g, float bl);
void queen2(unsigned int& bezierVAO, unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether, float x, float y, float z, float h,
    float w, float b, float r, float g, float bl);
void king1(unsigned int& bezierVAO, unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether, float x, float y, float z, float h, float w,
    float b, float r, float g, float bl, float cube_x, float cube_y, float cube_z);
void king2(unsigned int& bezierVAO, unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether, float x, float y, float z, float h, float w,
    float b, float r, float g, float bl, float cube_x, float cube_y, float cube_z);
void rook1(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether, float cube_x, float cube_y, float cube_z,
    float cube_height, float cube_w, float cube_b, float r, float g, float b);
void rook2(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether, float cube_x, float cube_y, float cube_z,
    float cube_height, float cube_w, float cube_b, float r, float g, float b);
void rook3(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether, float cube_x, float cube_y, float cube_z,
    float cube_height, float cube_w, float cube_b, float r, float g, float b);
void rook4(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether, float cube_x, float cube_y, float cube_z,
    float cube_height, float cube_w, float cube_b, float r, float g, float b);

unsigned int loadTexture(char const* path, GLenum textureWrappingModeS, GLenum textureWrappingModeT, GLenum textureFilteringModeMin, GLenum textureFilteringModeMax);


long long nCr(int n, int r);
void BezierCurve(double t, float xy[2], GLfloat ctrlpoints[], int L);
unsigned int hollowBezier(GLfloat ctrlpoints[], int L);

bool stopCurveRender=false;
// settings
const unsigned int SCR_WIDTH = 1400;
const unsigned int SCR_HEIGHT = 1000;

// modelling transform
float rotateAngle_X = 0.0;
float rotateAngle_Y = 0.0;
float rotateAngle_Z = 0.0;
float rotateAxis_X = 0.0;
float rotateAxis_Y = 0.0;
float rotateAxis_Z = 1.0;
float translate_X = 0.0;
float translate_Y = 0.0;
float translate_Z = 0.0;
float scale_X = 1.0;
float scale_Y = 1.0;
float scale_Z = 1.0;

float angle_r = 0, speed = 0.1f;
// camera
Camera camera(glm::vec3(2.0f, 3.0f, 7.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

float eyeX = 0.0, eyeY = 0.0, eyeZ = -1.0;
float lookAtX = 0.0, lookAtY = 0.0, lookAtZ = 0.0;
glm::vec3 V = glm::vec3(0.0f, 1.0f, 0.0f);
BasicCamera basic_camera(eyeX, eyeY, eyeZ, lookAtX, lookAtY, lookAtZ, V);

// viewport
GLint viewport[4];


vector <float> cntrlPoints= {
0.0300, 2.2650, 5.1000,
-0.3400, 1.8950, 5.1000,
-0.6050, 1.5500, 5.1000,
-0.0100, 0.8700, 5.1000,
};

vector <float> controlPointsForAll = {
0.4400, 2.1150, 5.1000,
0.3150, 1.8250, 5.1000,
0.3100, 1.4700, 5.1000,
0.4500, 1.0900, 5.1000,
0.6050, 0.8750, 5.1000,
};



vector <float> coordinates;
vector <float> normals;
vector <int> indices;
vector <float> vertices;
const double pi = 3.14159265389;
const int nt = 40;
const int ntheta = 20;
bool showControlPoints = true;
bool loadBezierCurvePoints = false;
bool showHollowBezier = false;
bool lineMode = false;
unsigned int bezierVAOforKing;
unsigned int bezierVAOforBishop;
unsigned int  bezierVAOforAll;

bool pressForPawn1=false;
bool pressForPawn2 = false;
bool pressForPawn3 = false;
bool pressForPawn4 = false;
bool pressForPawn5 = false;
bool pressForPawn6 = false;
bool pressForPawn7 = false;
bool pressForPawn8 = false;
bool pressForPawn9 = false;
bool pressForPawn10 = false;
bool pressForPawn11 = false;
bool pressForPawn12 = false;
bool pressRforBishop1= false;
bool pressLforBishop1= false;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float zForPawn1Cube = 0.8125f, zForPawn2Cube = 0.8125f,zForPawn3Cube = 0.8125,zForPawn4Cube = 0.8125f, zForPawn5Cube = 0.8125f, zForPawn6Cube = 0.8125f;
float zForPawn1Sphere = 0.875f, zForPawn2Sphere = 0.875f, zForPawn3Sphere = 0.875f, zForPawn4Sphere = 0.875f, zForPawn5Sphere = 0.875f, zForPawn6Sphere = 0.875f ;


float zForPawn7Cube2 = 2.0625f, zForPawn8Cube2 = 2.0625f, zForPawn9Cube2 = 2.0625f, zForPawn10Cube2 = 2.0625f, zForPawn11Cube2 = 2.0625f, zForPawn12Cube2 = 2.0625f;
float zForPawn7Sphere2 = 0.875f+1.25f, zForPawn8Sphere2 = 0.875f + 1.25f, zForPawn9Sphere2 = 0.875f + 1.25f, zForPawn10Sphere2 = 0.875f + 1.25f, zForPawn11Sphere2 = 0.875f + 1.25f, zForPawn12Sphere2 = 0.875f + 1.25f;


float xForBishop1 = 0.375f,zForBishop1=2.375f,yForBishop1=0.405f;
float xForBishop1Cube = 0.069f+0.25f, yForBishop1Cube = 0.25f, zForBishop1Cube = 2.325f;

float xForBishop2 = 0.375f+0.75f, zForBishop2 = 2.375f, yForBishop2 = 0.405f;
float xForBishop2Cube = 0.069f + 0.25f + 0.75, yForBishop2Cube = 0.25f, zForBishop2Cube = 2.325f;

float xForBishop3 = 0.375f, zForBishop3 = 2.375f - 1.75f, yForBishop3 = 0.405f;
float xForBishop3Cube = 0.069f + 0.25f, yForBishop3Cube = 0.25f, zForBishop3Cube = 2.325f - 1.75f;

float xForBishop4 = 0.375f+0.75, zForBishop4= 2.375f-1.75f, yForBishop4 = 0.405f;
float xForBishop4Cube = 0.069f + 0.25f + 0.75, yForBishop4Cube = 0.25f, zForBishop4Cube = 2.325f - 1.75f;

float xforQueen1 = 0.625f, zforQueen1 = 2.375f;
float xforQueen2 = 0.625f, zforQueen2 = 0.625f;

float xforKing1= 0.875f, yforKing1 = 0.175f, zforKing1= 2.375f;
float xForKing1Cube = 0.875f, yForKing1Cube = 0.25f, zForKing1Cube = 2.325f;

float xforKing2 = 0.875f, yforKing2= 0.175f, zforKing2 = 0.625f;
float xForKing2Cube = 0.875f, yForKing2Cube = 0.25f, zForKing2Cube = 0.625f;

float xforRook1 = 0.00f, zforRook1 = 2.375f - 0.775f;
float xforRook2 = 1.25f,  zforRook2 = 2.375f- 0.775f;
float xforRook3 = 0.00f, zforRook3 = 2.375f - 2.525f;
float xforRook4 = 1.25f, zforRook4 = 2.375f - 2.525f ;



// positions of the point lights
glm::vec3 pointLightPositions[] = {
    glm::vec3(0.2f,  4.8f,  2.5f),
    glm::vec3(9.8f,  4.8f,  2.5f),
    glm::vec3(0.2f,  9.8f,  2.5f),
    glm::vec3(9.8f,  9.8f,  2.5f),
    glm::vec3(6.0f,  13.8f,  6.0f),
};
PointLight pointlight1(

    pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    0.8f, 0.8f, 0.8f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    1       // light number
);
PointLight pointlight2(

    pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    0.8f, 0.8f, 0.8f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    2       // light number
);
PointLight pointlight3(

    pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    0.8f, 0.8f, 0.8f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    3       // light number
);
PointLight pointlight4(

    pointLightPositions[3].x, pointLightPositions[3].y, pointLightPositions[3].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    0.8f, 0.8f, 0.8f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    4      // light number
);
PointLight pointlight5(

    pointLightPositions[4].x, pointLightPositions[4].y, pointLightPositions[4].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    0.8f, 0.8f, 0.8f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    5       // light number
);

DirectionalLight directionalLight(-5.0f, -2.0f, 3.0f,
    0.05f, 0.05f, 0.05f,
    0.5f, 0.5f, 0.5f,
    .70f, 0.70f, 0.70f);


//SpotLight spotLight1(5.0f, 4.8f, 2.5f,
//    0, -1.0f, 0, 
//    1.0f, 1.0f, 0.05f,
//    0.8f, 0.8f, 0.8f,
//    1.0f, 1.0f, 1.0f, glm::cos(glm::radians(180.0f)), glm::cos(glm::radians(180.0f)));

//SpotLight spotLight2(5.0f, -10.0f, 2.5f,
//    0, -1.0f, 0, 0.05f,
//    0.05f, 0.05f,
//    0.8f, 0.8f, 0.8f,
//    1.0f, 1.0f, 1.0f, glm::cos(glm::radians(10.0f)), glm::cos(glm::radians(150.0f)));

SpotLight spotLight2(5.0f, -10.0f, 2.5f,
    0, -1.0f, 0, 0.05f,
    0.05f, 0.05f,
    0.8f, 0.8f, 0.8f,
    1.0f, 1.0f, 1.0f, glm::cos(glm::radians(210.0f)), glm::cos(glm::radians(120.0f)));

// light settings
bool pointLight1On = true;
bool pointLight3On = true;
bool pointLight2On = true;
bool pointLight4On = true;
bool pointLight5On = true;
bool ambientToggle = true;
bool diffuseToggle = true;
bool specularToggle = true;
bool directionalLightOn = true;
bool spotLightOn = true;
bool paOn = true;
bool pdOn = true;
bool psOn = true;
bool saOn = true;
bool sdOn = true;
bool ssOn = true;
bool pointLightOn = true;

// timing
float deltaTime = 0.0f;    // time between current frame and last frame
float lastFrame = 0.0f;

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    cout << "press F1,F2,F3,F4,F5,F6 and UP for pawn 1,2,3,4,5,6"<<endl;
    cout << "press F7,F8,F9,F10,F11,F12 and UP for pawn 7,8,9,10,11,12" << endl;
    cout << "press K and F1+F2 or F3+F4 for Bishop 1" << endl;
    cout << "press L,O,P and UP or DOWN and LEFT or RIGHT for BISHOP 2,3,4" << endl;
    cout << "press INSERT,DEL and UP,DOWN,LEFT,RIGHT or F1,F2,F3,F4 for KING 1 and 2" << endl;
    cout << "press PAGE_UP,PAGE_DOWN and UP,DOWN,LEFT,RIGHT or F1,F2,F3,F4 for QUEEN 1 and 2" << endl;

    cout << "press 1 to turn pointlights 1 and 3 on or off" << endl;
    cout << "press 2 to turn pointlights 2,4 and 5 on or off" << endl;
    cout << "press 3 to turn spotlight on or off" << endl;
    cout << "press 4 to turn directional light on or off" << endl;
    cout << "press 5 to turn ambient light on or off" << endl;
    cout << "press 6 to turn diffusion light on or off" << endl;
    cout << "press 7 to turn specular light on or off" << endl;
    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "CSE 4208: Computer Graphics Laboratory", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile our shader zprogram
// ------------------------------------
    Shader lightingShader("vertexShaderForPhongShading.vs", "fragmentShaderForPhongShading.fs");
    Shader lightingShaderWithTexture("vertexShaderForPhongShadingWithTexture.vs", "fragmentShaderForPhongShadingWithTexture.fs");
    Shader ourShader("vertexShader.vs", "fragmentShader.fs");

    string diffuseMapPath = "floor.png";
    string specularMapPath = "container2_specular.png";


    unsigned int diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube = Cube(diffMap, specMap, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    ////////////////
    string diffuseMapPath2 = "wall.jpg";
    string specularMapPath2 = "white.jpg";


    unsigned int diffMap2 = loadTexture(diffuseMapPath2.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap2 = loadTexture(specularMapPath2.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube2 = Cube(diffMap2, specMap2, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    ////////////////
    string diffuseMapPath3 = "clock.jpg";
    string specularMapPath3 = "white.jpg";


    unsigned int diffMap3 = loadTexture(diffuseMapPath3.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap3 = loadTexture(specularMapPath3.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube3= Cube(diffMap3, specMap3, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------

    float cube_vertices[] = {
        // positions      // normals
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
        1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
        1.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,
        0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,

        1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

        0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,

        0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,

        1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,

        0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
        1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
        1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f
    };
    unsigned int cube_indices[] = {
        0, 3, 2,
        2, 1, 0,

        4, 5, 7,
        7, 6, 4,

        8, 9, 10,
        10, 11, 8,

        12, 13, 14,
        14, 15, 12,

        16, 17, 18,
        18, 19, 16,

        20, 21, 22,
        22, 23, 20
    };

    unsigned int cubeVAO, cubeVBO, cubeEBO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &cubeVBO);
    glGenBuffers(1, &cubeEBO);

    glBindVertexArray(cubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);


    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // vertex normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)12);
    glEnableVertexAttribArray(1);

    // second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
    unsigned int lightCubeVAO;
    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO);
    // note that we update the lamp's position attribute's stride to reflect the updated buffer data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);



    bezierVAOforAll = hollowBezier(controlPointsForAll.data(), ((unsigned int)controlPointsForAll.size() / 3) - 1);
    //bezierVAOforKing = hollowBezier(cntrlPoints2.data(), ((unsigned int)cntrlPoints2.size() / 3) - 1);

    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // be sure to activate shader when setting uniforms/drawing objects
        lightingShader.use();
        lightingShader.setVec3("viewPos", camera.Position);

        // set up lights
        pointlight1.setUpPointLight(lightingShader);
        pointlight3.setUpPointLight(lightingShader);
        pointlight2.setUpPointLight(lightingShader);
        pointlight4.setUpPointLight(lightingShader);
        pointlight5.setUpPointLight(lightingShader);
        directionalLight.setUpDirectionalLight(lightingShader);
        spotLight2.setUpSpotLight(lightingShader);

        lightingShader.use();

        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        lightingShader.setMat4("projection", projection);

        glm::mat4 view = camera.GetViewMatrix();
        lightingShader.setMat4("view", view);

        // Modelling Transformation
        glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, modelforChessBoard;
        translateMatrix = glm::translate(identityMatrix, glm::vec3(translate_X, translate_Y, translate_Z));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(scale_X, scale_Y, scale_Z));
        modelforChessBoard = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        lightingShader.setMat4("model", modelforChessBoard);

        //Render the chess board and pieces
        chess_board(cubeVAO, lightingShader, modelforChessBoard);

        glm::mat4 modelForQueen;
        identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        translateMatrix = glm::translate(identityMatrix, glm::vec3(translate_X, translate_Y, translate_Z));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(scale_X, scale_Y, scale_Z));
        modelForQueen = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        lightingShader.setMat4("model", modelForQueen);


      queen1(bezierVAOforAll, cubeVAO, lightingShader, modelForQueen, xforQueen1, 0.175f, zforQueen1, 0.10f, 0.20f, 0.10f,0.1, 0.5, 0.8);
      queen2(bezierVAOforAll, cubeVAO, lightingShader, modelForQueen, xforQueen2, 0.175f, zforQueen2, 0.10f, 0.20f, 0.10f, 1.0, 1.0, 1.0);

       glm::mat4 modelForKing;
       identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
       translateMatrix = glm::translate(identityMatrix, glm::vec3(translate_X, translate_Y, translate_Z));
       rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
       rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
       rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
       scaleMatrix = glm::scale(identityMatrix, glm::vec3(scale_X, scale_Y, scale_Z));
       modelForKing = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
       lightingShader.setMat4("model", modelForKing);


      king1(bezierVAOforAll, cubeVAO, lightingShader, modelForKing, xforKing1, yforKing1, zforKing1, 0.10f, 0.20f, 0.10f, 0.1, 0.5, 0.8,xForKing1Cube,yForKing1Cube,zForKing1Cube);
      king2(bezierVAOforAll, cubeVAO, lightingShader, modelForKing, xforKing2, yforKing2, zforKing2, 0.10f, 0.20f, 0.10f, 1.0, 1.0, 1.0,xForKing2Cube,yForKing2Cube,zForKing2Cube);

       glm::mat4 modelForRook;
       identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
       translateMatrix = glm::translate(identityMatrix, glm::vec3(translate_X, translate_Y, translate_Z));
       rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
       rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
       rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
       scaleMatrix = glm::scale(identityMatrix, glm::vec3(scale_X, scale_Y, scale_Z));
       modelForRook = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
       lightingShader.setMat4("model", modelForRook);

       rook1(cubeVAO, lightingShader, modelForKing, xforRook1,-0.125f,zforRook1,0.15,0.1,0.1, 0.1,0.5,0.8);
       rook2(cubeVAO, lightingShader, modelForKing, xforRook2,-0.125f,zforRook2,0.15,0.1,0.1,0.1,0.5,0.8);
       rook3(cubeVAO, lightingShader, modelForKing, xforRook3,-0.125f,zforRook3,0.15,0.1,0.1,1.0,1.0,1.0);
       rook4(cubeVAO, lightingShader, modelForKing, xforRook4,-0.125f,zforRook4,0.15,0.1, 0.1, 1.0,1.0,1.0);
         
        glm::mat4 modelForPawn;
        identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        translateMatrix = glm::translate(identityMatrix, glm::vec3(translate_X, translate_Y, translate_Z));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(scale_X, scale_Y, scale_Z));
        modelForPawn = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        lightingShader.setMat4("model", modelForPawn);

    
        pawn1(bezierVAOforAll,cubeVAO, lightingShader, modelForPawn, 0.0625f, 0.25f, zForPawn1Cube, 0.15, 0.25, 0.15f, 0.125f, 0.525f, zForPawn1Sphere, 0.05, 0.05, 0.05f, 1.0, 1.0, 1.0);
        pawn2(bezierVAOforAll, cubeVAO, lightingShader, modelForPawn, 0.3125f, 0.25f, zForPawn2Cube, 0.15, 0.25, 0.15f, 0.125f + 0.25f, 0.525f, zForPawn2Sphere, 0.05, 0.05, 0.05f, 1.0, 1.0, 1.0);
        pawn3(bezierVAOforAll, cubeVAO, lightingShader, modelForPawn, 0.5625f, 0.25f, zForPawn3Cube, 0.15, 0.25, 0.15f, 0.125f + 0.25 * 2.0, 0.525f, zForPawn3Sphere, 0.05, 0.05, 0.05f, 1.0, 1.0, 1.0);
        pawn4(bezierVAOforAll, cubeVAO, lightingShader, modelForPawn, 0.8125f, 0.25f, zForPawn4Cube, 0.15, 0.25, 0.15f, 0.125f + 0.25 * 3.0, 0.525f, zForPawn4Sphere, 0.05, 0.05, 0.05f, 1.0, 1.0, 1.0);
        pawn5(bezierVAOforAll, cubeVAO, lightingShader, modelForPawn, 1.0625f, 0.25f, zForPawn5Cube, 0.15, 0.25, 0.15f, 0.125f + 0.25 * 4.0, 0.525f, zForPawn5Sphere, 0.05, 0.05, 0.05f, 1.0, 1.0, 1.0);
        pawn6(bezierVAOforAll, cubeVAO, lightingShader, modelForPawn, 1.3125f, 0.25f, zForPawn6Cube, 0.15, 0.25, 0.15f, 0.125f + 0.25 * 5.0, 0.525f, zForPawn6Sphere, 0.05, 0.05, 0.05f, 1.0, 1.0, 1.0);

        pawn7(bezierVAOforAll, cubeVAO, lightingShader, modelForPawn, 0.0625f, 0.25f, zForPawn7Cube2, 0.15, 0.25, 0.15f, 0.125f, 0.525f, zForPawn7Sphere2, 0.05, 0.05, 0.05f, 0.1, 0.5, 0.8);
        pawn8(bezierVAOforAll, cubeVAO, lightingShader, modelForPawn, 0.3125f, 0.25f, zForPawn8Cube2, 0.15, 0.25, 0.15f, 0.125f + 0.25f, 0.525f, zForPawn8Sphere2, 0.05, 0.05, 0.05f, 0.1, 0.5, 0.8);
        pawn9(bezierVAOforAll, cubeVAO, lightingShader, modelForPawn, 0.5625f, 0.25f, zForPawn9Cube2, 0.15, 0.25, 0.15f, 0.125f + 0.25 * 2.0, 0.525f, zForPawn9Sphere2, 0.05, 0.05, 0.05f, 0.1, 0.5, 0.8);
        pawn10(bezierVAOforAll, cubeVAO, lightingShader, modelForPawn, 0.8125f, 0.25f, zForPawn10Cube2, 0.15, 0.25, 0.15f, 0.125f + 0.25 * 3.0, 0.525f, zForPawn10Sphere2, 0.05, 0.05, 0.05f, 0.1, 0.5, 0.8);
        pawn11(bezierVAOforAll, cubeVAO, lightingShader, modelForPawn, 1.0625f, 0.25f, zForPawn11Cube2, 0.15, 0.25, 0.15f, 0.125f + 0.25 * 4.0, 0.525f, zForPawn11Sphere2, 0.05, 0.05, 0.05f, 0.1, 0.5, 0.8);
        pawn12(bezierVAOforAll, cubeVAO, lightingShader, modelForPawn, 1.3125f, 0.25f, zForPawn12Cube2, 0.15, 0.25, 0.15f, 0.125f + 0.25 * 5.0, 0.525f, zForPawn12Sphere2, 0.05, 0.05, 0.05f, 0.1, 0.5, 0.8);
               
        if (pressForPawn1)
        {
            zForPawn1Cube += 0.25f;
            zForPawn1Sphere += 0.25f;
            pawn1(bezierVAOforAll,cubeVAO, lightingShader, modelForPawn, 0.0625f, 0.25f, zForPawn1Cube, 0.15, 0.25, 0.15f, 0.125f, 0.525f, zForPawn1Sphere, 0.05, 0.05, 0.05f, 1.0, 1.0, 1.0);
            pressForPawn1 = false;
         
        }
        if (pressForPawn2)
        {
            zForPawn2Cube += 0.25f;
            zForPawn2Sphere += 0.25f;
            pawn2(bezierVAOforAll, cubeVAO, lightingShader, modelForPawn, 0.3125f, 0.25f, zForPawn2Cube, 0.15, 0.25, 0.15f, 0.125f + 0.25f, 0.525f, zForPawn2Sphere, 0.05, 0.05, 0.05f, 1.0, 1.0, 1.0);
            pressForPawn2 = false;
        }
        if (pressForPawn3)
        {
            zForPawn3Cube += 0.25f;
            zForPawn3Sphere += 0.25f;
            pawn3(bezierVAOforAll, cubeVAO, lightingShader, modelForPawn, 0.5625f, 0.25f, zForPawn3Cube , 0.15, 0.25, 0.15f, 0.125f + 0.25 * 2.0, 0.525f, zForPawn3Sphere, 0.05, 0.05, 0.05f, 1.0, 1.0, 1.0);
            pressForPawn3 = false;
        }
        if (pressForPawn4)
        {
            zForPawn4Cube += 0.25f;
            zForPawn4Sphere += 0.25f;
            pawn4(bezierVAOforAll, cubeVAO, lightingShader, modelForPawn, 0.8125f, 0.25f, zForPawn4Cube , 0.15, 0.25, 0.15f, 0.125f + 0.25 * 3.0, 0.525f, zForPawn4Sphere, 0.05, 0.05, 0.05f, 1.0, 1.0, 1.0);
            pressForPawn4 = false;
        }
        if (pressForPawn5)
        {
            zForPawn5Cube += 0.25f;
            zForPawn5Sphere += 0.25f;
            pawn5(bezierVAOforAll, cubeVAO, lightingShader, modelForPawn, 1.0625f, 0.25f, zForPawn5Cube , 0.15, 0.25, 0.15f, 0.125f + 0.25 * 4.0, 0.525f, zForPawn5Sphere, 0.05, 0.05, 0.05f, 1.0, 1.0, 1.0);
            pressForPawn5 = false;
        }
        if (pressForPawn6)
        {
            zForPawn6Cube += 0.25f;
            zForPawn6Sphere += 0.25f;
            pawn6(bezierVAOforAll, cubeVAO, lightingShader, modelForPawn, 1.3125f, 0.25f, zForPawn6Cube , 0.15, 0.25, 0.15f, 0.125f + 0.25 * 5.0, 0.525f, zForPawn6Sphere, 0.05, 0.05, 0.05f, 1.0, 1.0, 1.0);
            pressForPawn6 = false;
        }
        if (pressForPawn7)
        {
            zForPawn7Cube2 -= 0.25f;
            zForPawn7Sphere2 -= 0.25f;
            pawn7(bezierVAOforAll, cubeVAO, lightingShader, modelForPawn, 0.0625f, 0.25f, zForPawn7Cube2, 0.15, 0.25, 0.15f, 0.125f, 0.525f, zForPawn7Sphere2, 0.05, 0.05, 0.05f, 0.1, 0.5, 0.8);
            pressForPawn7 = false;
        }
        if (pressForPawn8)
        {
            zForPawn8Cube2 -= 0.25f;
            zForPawn8Sphere2 -= 0.25f;
            pawn8(bezierVAOforAll, cubeVAO, lightingShader, modelForPawn, 0.3125f, 0.25f, zForPawn8Cube2, 0.15, 0.25, 0.15f, 0.125f + 0.25f, 0.525f, zForPawn8Sphere2, 0.05, 0.05, 0.05f, 0.1, 0.5, 0.8);
            pressForPawn8 = false;
        }

        if (pressForPawn9)
        {
            zForPawn9Cube2 -= 0.25f;
            zForPawn9Sphere2 -= 0.25f;
            pawn9(bezierVAOforAll, cubeVAO, lightingShader, modelForPawn, 0.5625f, 0.25f, 2.0625f, 0.15, 0.25, 0.15f, 0.125f + 0.25 * 2.0, 0.525f, zForPawn9Sphere2, 0.05, 0.05, 0.05f, 0.1, 0.5, 0.8);
            pressForPawn9 = false;
        }

        if (pressForPawn10)
        {
            zForPawn10Cube2 -= 0.25f;
            zForPawn10Sphere2 -= 0.25f;
            pawn10(bezierVAOforAll, cubeVAO, lightingShader, modelForPawn, 0.8125f, 0.25f, zForPawn10Cube2, 0.15, 0.25, 0.15f, 0.125f + 0.25 * 3.0, 0.525f, zForPawn10Sphere2, 0.05, 0.05, 0.05f, 0.1, 0.5, 0.8);
            pressForPawn10 = false;
        }

        if (pressForPawn11)
        {
            zForPawn11Cube2 -= 0.25f;
            zForPawn11Sphere2 -= 0.25f;
            pawn11(bezierVAOforAll, cubeVAO, lightingShader, modelForPawn, 1.0625f, 0.25f, 2.0625f, 0.15, 0.25, 0.15f, 0.125f + 0.25 * 4.0, 0.525f, zForPawn11Sphere2, 0.05, 0.05, 0.05f, 0.1, 0.5, 0.8);
            pressForPawn11 = false;
        }

        if (pressForPawn12)
        {
            zForPawn12Cube2 -= 0.25f;
            zForPawn12Sphere2 -= 0.25f;
            pawn12(bezierVAOforAll, cubeVAO, lightingShader, modelForPawn, 1.3125f, 0.25f, 2.0625f, 0.15, 0.25, 0.15f, 0.125f + 0.25 * 5.0, 0.525f, zForPawn12Sphere2, 0.05, 0.05, 0.05f, 0.1, 0.5, 0.8);
            pressForPawn12 = false;
        }

        glm::mat4 modelforBishop;
        identityMatrix = glm::mat4(1.0f); 
        translateMatrix = glm::translate(identityMatrix, glm::vec3(translate_X, translate_Y, translate_Z));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(scale_X, scale_Y, scale_Z));
        modelforBishop = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        lightingShader.setMat4("model", modelforBishop);

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////

        bishop1(bezierVAOforAll, cubeVAO, lightingShader, modelforBishop, xForBishop1, 0.405f, zForBishop1,0.05f, 0.05f, 0.04f, 0.1, 0.5, 0.8, xForBishop1Cube, yForBishop1Cube, zForBishop1Cube);
        bishop2(bezierVAOforAll, cubeVAO, lightingShader, modelforBishop, xForBishop2, 0.405f, zForBishop2,0.05f, 0.05f, 0.04f, 0.1, 0.5, 0.8, xForBishop2Cube , yForBishop2Cube, zForBishop2Cube);
        bishop3(bezierVAOforAll, cubeVAO, lightingShader, modelforBishop, xForBishop3, 0.405f, zForBishop3,0.05f, 0.05f, 0.04f, 1.0, 1.0, 1.0, xForBishop3Cube, yForBishop3Cube, zForBishop3Cube);
        bishop4(bezierVAOforAll, cubeVAO, lightingShader, modelforBishop, xForBishop4, 0.405f, zForBishop4,0.05f, 0.05f, 0.04f, 1.0, 1.0, 1.0, xForBishop4Cube , yForBishop4Cube, zForBishop4Cube);

        glm::mat4 modelForLighting;
       //glm::mat4 modelForLighting2;
        //glm::mat4 modelForLighting3;
        glm::mat4 translate = glm::mat4(1.0f);
        glm::mat4 scale = glm::mat4(1.0f);
        glm::mat4 rotate = glm::mat4(1.0f);

        modelForLighting = glm::mat4(1.0f);//point_light 
        modelForLighting = glm::translate(modelForLighting, glm::vec3(4.0f, 2.5f, 3.5f));
        modelForLighting = glm::scale(modelForLighting, glm::vec3(0.2f)); // Make it a smaller cube
        ourShader.setMat4("model", modelForLighting);
        ourShader.setVec3("color", glm::vec3(1.0f, 1.0f, 0.8f));

        if (!pointLight1On) {
            ourShader.setVec3("color", glm::vec3(0.0f, 0.0f, 0.0f));
        }
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        modelForLighting = glm::mat4(1.0f);//spot_light 
        modelForLighting = glm::translate(modelForLighting, glm::vec3(3.0f, 2.5f, 2.5f));
        modelForLighting = glm::scale(modelForLighting, glm::vec3(0.2f));
        ourShader.setMat4("model", modelForLighting);
        ourShader.setVec3("color", glm::vec3(0.0f, 0.0f, 0.0f));
        if (!spotLightOn) {
            ourShader.setVec3("color", glm::vec3(0.0f, 0.0f, 0.0f));
        }
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);



        lightingShaderWithTexture.use();
        lightingShaderWithTexture.setVec3("viewPos", camera.Position);
        lightingShaderWithTexture.setMat4("projection", projection);
        lightingShaderWithTexture.setMat4("view", view);
        lightingShaderWithTexture.use(); // check for double usage

        pointlight1.setUpPointLight(lightingShaderWithTexture);
        pointlight2.setUpPointLight(lightingShaderWithTexture);
        pointlight4.setUpPointLight(lightingShaderWithTexture);
        pointlight3.setUpPointLight(lightingShaderWithTexture);
        pointlight5.setUpPointLight(lightingShaderWithTexture);

        directionalLight.setUpDirectionalLight(lightingShaderWithTexture);
        //spotLight1.setUpSpotLight(lightingShaderWithTexture);
        spotLight2.setUpSpotLight(lightingShaderWithTexture);

        //table
        glm::mat4 modelforTable = glm::mat4(1.0f);
        lightingShaderWithTexture.use();
        translate = glm::mat4(1.0f);
        scale = glm::mat4(1.0f);
        rotate = glm::mat4(1.0f);
        scale = glm::scale(modelforTable, glm::vec3(4.0f, 0.20f, 4.0f));
        translate = glm::translate(modelforTable, glm::vec3(-0.25f, -0.25f,- 0.20f));
        modelforTable =scale * translate;
        cube.drawCubeWithTexture(lightingShaderWithTexture, modelforTable);

        lightingShaderWithTexture.use();
        modelforTable = glm::mat4(1.0f);
        translate = glm::mat4(1.0f);
        scale = glm::mat4(1.0f);
        rotate = glm::mat4(1.0f);
        scale = glm::scale(modelforTable, glm::vec3(0.4f, 4.00f, 0.4f));
        translate = glm::translate(modelforTable, glm::vec3(-2.5f, -1.00f, -2.00f));
        modelforTable = scale * translate;
        cube.drawCubeWithTexture(lightingShaderWithTexture, modelforTable);

        lightingShaderWithTexture.use();
        modelforTable = glm::mat4(1.0f);
        translate = glm::mat4(1.0f);
        scale = glm::mat4(1.0f);
        rotate = glm::mat4(1.0f);
        scale = glm::scale(modelforTable, glm::vec3(0.4f, 4.00f, 0.4f));
        translate = glm::translate(modelforTable, glm::vec3(6.5f, -1.00f, -2.00f));
        modelforTable = scale * translate;
        cube.drawCubeWithTexture(lightingShaderWithTexture, modelforTable);

        lightingShaderWithTexture.use();
        modelforTable = glm::mat4(1.0f);
        translate = glm::mat4(1.0f);
        scale = glm::mat4(1.0f);
        rotate = glm::mat4(1.0f);
        scale = glm::scale(modelforTable, glm::vec3(0.4f, 4.00f, 0.4f));
        translate = glm::translate(modelforTable, glm::vec3(-2.5f, -1.00f, 7.00f));
        modelforTable = scale * translate;
        cube.drawCubeWithTexture(lightingShaderWithTexture, modelforTable);

        lightingShaderWithTexture.use();
        modelforTable = glm::mat4(1.0f);
        translate = glm::mat4(1.0f);
        scale = glm::mat4(1.0f);
        rotate = glm::mat4(1.0f);
        scale = glm::scale(modelforTable, glm::vec3(0.4f, 4.00f, 0.4f));
        translate = glm::translate(modelforTable, glm::vec3(6.5f, -1.00f, 7.00f));
        modelforTable = scale * translate;
        cube.drawCubeWithTexture(lightingShaderWithTexture, modelforTable);
        //room
        lightingShaderWithTexture.use();
        modelforTable = glm::mat4(1.0f);
        translate = glm::mat4(1.0f);
        scale = glm::mat4(1.0f);
        translate = glm::translate(modelforTable, glm::vec3(-0.5f, -0.25f, -0.50f));
        scale = glm::scale(modelforTable, glm::vec3(25.125f*1.75f, 15.25f, 25.125f* 1.75f));
        modelforTable = scale * translate;
        cube2.drawCubeWithTexture(lightingShaderWithTexture, modelforTable);

        //clock
        
        glm::mat4 modelforClock = glm::mat4(1.0f);
        translate = glm::mat4(1.0f);
        scale = glm::mat4(1.0f);
        rotate = glm::rotate(identityMatrix, glm::radians(angle_r), glm::vec3(0.0f, 1.0f, 0.0f));
        modelforClock = translate *scale;
        clock1(cubeVAO, lightingShader, modelforClock);

        modelforClock = glm::mat4(1.0f);
        translate = glm::mat4(1.0f);
        scale = glm::mat4(1.0f);
        translate = glm::translate(modelforClock, glm::vec3(0.300f, 0.3125f, -21.50f));
        scale = glm::scale(modelforClock, glm::vec3(2.125f, 2.125f, 0.01f));
        modelforClock =  translate*scale;
        cube3.drawCubeWithTexture(lightingShaderWithTexture, modelforClock);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &bezierVAOforBishop);
    glDeleteVertexArrays(1, &bezierVAOforKing);
    glDeleteVertexArrays(1, &bezierVAOforAll);
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &lightCubeVAO);
    glDeleteBuffers(1, &cubeVBO);
    glDeleteBuffers(1, &cubeEBO);

    glfwTerminate();
    return 0;
}

void drawCube(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 model = glm::mat4(1.0f), float r = 1.0f, float g = 1.0f, float b = 1.0f)
{
    lightingShader.use();
    lightingShader.setVec3("material.ambient", glm::vec3(r, g, b));
    lightingShader.setVec3("material.diffuse", glm::vec3(r, g, b));
    lightingShader.setVec3("material.specular", glm::vec3(0.5f, 0.5f, 0.5f));
    lightingShader.setFloat("material.shininess", 32.0f);

    lightingShader.setMat4("model", model);
    glBindVertexArray(cubeVAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void drawCurve(unsigned int& bezierVAO, Shader& lightingShader, glm::mat4 model, float r , float g, float b )
{
    lightingShader.use();
    lightingShader.setMat4("model", model);
    lightingShader.setVec3("material.ambient", glm::vec3(r, g, b));
    lightingShader.setVec3("material.diffuse", glm::vec3(r, g, b));
    lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
    lightingShader.setFloat("material.shininess", 32.0f);

    glBindVertexArray(bezierVAO);
    glDrawElements(GL_TRIANGLES, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
    glBindVertexArray(0);
}

void queen1(unsigned int& bezierVAO, unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether, float x, float y, float z, float h, float w, 
    float b,float r, float g, float bl) {

    glm::mat4 modelForQueen = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    glm::mat4 rotate = glm::mat4(1.0f);
    translate = glm::translate(modelForQueen, glm::vec3(x, y, z));
    scale = glm::scale(modelForQueen, glm::vec3(h, w, b));
    modelForQueen = alTogether * translate * scale;
    drawCurve(bezierVAO, lightingShader, modelForQueen, r, g, bl);

    modelForQueen = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    rotate = glm::mat4(1.0f);
    modelForQueen = alTogether * translate * scale;
    drawSphere(lightingShader, alTogether * modelForQueen, x , 0.60, z, 0.09f, 0.03f, 0.09f, r, g, bl);

    modelForQueen = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    rotate = glm::mat4(1.0f);
    modelForQueen = alTogether * translate * scale;
    drawSphere(lightingShader, alTogether * modelForQueen, x, 0.505, z, 0.105f, 0.045f, 0.105f, r, g, bl);

    modelForQueen = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    rotate = glm::mat4(1.0f);
    modelForQueen = alTogether * translate * scale;
    drawSphere(lightingShader, alTogether * modelForQueen, x, 0.325, z, 0.15f, 0.075f, 0.15f, r, g, bl);

    modelForQueen = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    rotate = glm::mat4(1.0f);
    modelForQueen = alTogether * translate * scale;
    drawSphere(lightingShader, alTogether * modelForQueen, x, 0.625, z, 0.04f, 0.04f, 0.04f, r, g, bl);
}



void king1(unsigned int& bezierVAO, unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether, float x, float y, float z, float h, float w, 
    float b,float r, float g, float bl, float cube_x, float cube_y, float cube_z) {

    glm::mat4 modelForKing = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    glm::mat4 rotate = glm::mat4(1.0f);
    translate = glm::translate(modelForKing, glm::vec3(x, y, z));
    scale = glm::scale(modelForKing, glm::vec3(h, w, b));
    modelForKing = alTogether * translate * scale;
    drawCurve(bezierVAO, lightingShader, modelForKing, r, g, bl);

    modelForKing = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    rotate = glm::mat4(1.0f);
    modelForKing = alTogether * translate * scale;
    drawSphere(lightingShader, alTogether * modelForKing, x, 0.60, z, 0.09f, 0.03f, 0.09f, r, g, bl);

    modelForKing = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    rotate = glm::mat4(1.0f);
    modelForKing = alTogether * translate * scale;
    drawSphere(lightingShader, alTogether * modelForKing, x, 0.505, z, 0.105f, 0.045f, 0.105f, r, g, bl);

    modelForKing = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    rotate = glm::mat4(1.0f);
    modelForKing = alTogether * translate * scale;
    drawSphere(lightingShader, alTogether * modelForKing, x, 0.325, z, 0.15f, 0.075f, 0.15f, r, g, bl);

    modelForKing = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    rotate = glm::mat4(1.0f);
    translate = glm::translate(modelForKing, glm::vec3(cube_x-0.01, cube_y+0.375, cube_z+0.045));
    scale = glm::scale(modelForKing, glm::vec3(0.02f, 0.06f, 0.02f));
    modelForKing = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, alTogether * modelForKing, r, g, bl);

    modelForKing = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    rotate = glm::mat4(1.0f);
    translate = glm::translate(modelForKing, glm::vec3(cube_x - 0.0325, cube_y + 0.395, cube_z + 0.045));
    scale = glm::scale(modelForKing, glm::vec3(0.06f, 0.02f, 0.02f));
    modelForKing = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, alTogether * modelForKing, r, g, bl);

}

void pawn1(unsigned int& bezierVAO, unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether, float cube_x, float cube_y, float cube_z,
    float cube_height, float cube_w, float cube_b, float sphere_x, float sphere_y, float sphere_z, float sphere_height, float sphere_w,
    float sphere_b, float r, float g, float b) {

    glm::mat4 modelforPawn = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    glm::mat4 rotate = glm::mat4(1.0f);
    translate = glm::translate(modelforPawn, glm::vec3(cube_x + 0.0625, cube_y, cube_z + 0.0675));
    scale = glm::scale(modelforPawn, glm::vec3(0.07, 0.12f, 0.07));
    modelforPawn = alTogether * translate * scale;
    drawCurve(bezierVAO, lightingShader, modelforPawn, r, g, b);

    modelforPawn = glm::mat4(1.0f);
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    modelforPawn = alTogether * translate * scale;
    drawSphere(lightingShader, alTogether * modelforPawn, sphere_x, sphere_y+0.025, sphere_z, sphere_height, sphere_w, sphere_b, 1.0, 1.0, 1.0);

    modelforPawn = glm::mat4(1.0f);
    identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    modelforPawn = alTogether * translate * scale;
    drawSphere(lightingShader, alTogether * modelforPawn, sphere_x, sphere_y-0.205f, sphere_z, 0.10f, 0.050f, 0.10f, 1.0, 1.0, 1.0);

    modelforPawn = glm::mat4(1.0f);
    identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    modelforPawn = alTogether * translate * scale;
    drawSphere(lightingShader, alTogether * modelforPawn, sphere_x, sphere_y-0.015, sphere_z, 0.08f, 0.025f, 0.08f, 1.0, 1.0, 1.0);

}
void bishop1(unsigned int& bezierVAO,unsigned int& cubeVAO,Shader& lightingShader, glm::mat4 alTogether, float x, float y, float z, float h, float w,
    float b, float r, float g, float bl, float cube_x, float cube_y, float cube_z) {

    glm::mat4 modelForBishop = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    glm::mat4 rotate = glm::mat4(1.0f);
    translate = glm::translate(modelForBishop, glm::vec3(x-0.01f, y+0.055, z));
    scale = glm::scale(modelForBishop, glm::vec3(h, w, b));
    modelForBishop = alTogether * translate * scale;
    drawCurve(bezierVAO, lightingShader, modelForBishop, r, g, bl);

    modelForBishop = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    rotate = glm::mat4(1.0f);
    modelForBishop = alTogether * translate * scale;
    drawSphere(lightingShader, alTogether * modelForBishop, xForBishop1-0.01f, yForBishop1+0.165f, zForBishop1, 0.0365f, 0.0365f, 0.0365f, 0.1, 0.5, 0.8);

    modelForBishop = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    rotate = glm::mat4(1.0f);
    modelForBishop = alTogether * translate * scale;
    drawSphere(lightingShader, alTogether * modelForBishop, xForBishop1, yForBishop1-0.105f, zForBishop1-0.01f, 0.2f, 0.01f, 0.2f, 0.1, 0.5, 0.8);

    modelForBishop = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    rotate = glm::mat4(1.0f);
    modelForBishop = alTogether * translate * scale;
    drawSphere(lightingShader, alTogether * modelForBishop, xForBishop1-0.01, yForBishop1 + 0.085f, zForBishop1, 0.15f, 0.05f, 0.15f, 0.1, 0.5, 0.8);

    modelForBishop = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    rotate = glm::mat4(1.0f);
    translate = glm::translate(modelForBishop, glm::vec3(xForBishop1Cube, yForBishop1Cube, zForBishop1Cube));
    scale = glm::scale(modelForBishop, glm::vec3(0.10f, 0.25f, 0.10f));
    modelForBishop = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, alTogether * modelForBishop, r, g, bl);

}

void drawSphere(Shader& lightingShader, glm::mat4 alTogether, float x, float y, float z, float h, float w, float b,float red,float green,float blue) 
{
    Sphere sphere = Sphere( 0.50f,  10, 20, glm::vec3(red, green, blue), glm::vec3(red, green, blue), glm::vec3(red, green, blue),  glm::vec3(red, green, blue), 1.0f) ;
    glm::mat4 modelForSphere = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    glm::mat4 rotate = glm::mat4(1.0f);
    translate = glm::translate(modelForSphere, glm::vec3(x, y, z));
    scale = glm::scale(modelForSphere, glm::vec3(h, w, b));
    modelForSphere = alTogether * translate * scale;
    sphere.drawSphere(lightingShader, modelForSphere);
   
}

void cube_1(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether,float x, float y, float z,
    float cube_height, float cube_w, float cube_b, float r, float g, float b) {
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    glm::mat4 rotate = glm::mat4(1.0f);

    model = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(x , y, z ));
    scale = glm::scale(model, glm::vec3(cube_height, cube_w, cube_b));
    model = alTogether * translate * scale;
    lightingShader.setMat4("model", model);
    drawCube(cubeVAO, lightingShader, alTogether * model, r, g, b);

}


void chess_board(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether) {
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    glm::mat4 rotate = glm::mat4(1.0f);

    float numRows = 2, numCols = 1.5;
    float squareWidth = 0.25f, squareHeight = 0.25f;

    // Iterate through rows and columns to create the chessboard
    for (float row = 0.0f; row < numRows; row = row + 0.25f) {
        for (float col = 0.0f; col < numCols; col = col + 0.25f) {
            model = glm::mat4(1.0f);
            translate = glm::translate(model, glm::vec3(0.0f + col, 0.25f , 0.50f + row));
            scale = glm::scale(model, glm::vec3(squareWidth, 0.05f, squareHeight)); 
            model = alTogether * translate * scale; 
            
            if ((int)(row * 4) % 2 == (int)(col * 4) % 2) {  
                drawCube(cubeVAO, lightingShader, alTogether * model, 1.0, 1.0, 1.0);
            }
            else {
               drawCube(cubeVAO, lightingShader, alTogether * model, 0.0, 0.0, 0.0);
            }
        }
    }
}

void clock1(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether) {

    glm::mat4 modelforClock = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    glm::mat4 rotate = glm::mat4(1.0f);
    rotate= glm::rotate(modelforClock, glm::radians(angle_r), glm::vec3(0.0f, 0.0f, 1.0f));

    angle_r -= speed;
    scale = glm::scale(modelforClock, glm::vec3(0.10, 0.8f, 0.1));
    translate = glm::translate(modelforClock, glm::vec3(1.5, 1.5, -21.0));
    modelforClock =  alTogether * translate*rotate *scale  ;
    drawCube(cubeVAO, lightingShader, modelforClock, 0.0f, 0.0f, 0.0f);

}
// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.ProcessKeyboard(LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.ProcessKeyboard(RIGHT, deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
    {
        if (rotateAxis_X) rotateAngle_X -= 0.1;
        else if (rotateAxis_Y) rotateAngle_Y -= 0.1;
        else rotateAngle_Z -= 0.1;
    }

    //if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) translate_Y += 0.001;
    //if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) translate_Y -= 0.001;
    //if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) translate_X += 0.001;
    //if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) translate_X -= 0.001;
    //if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) translate_Z += 0.001;
    //if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) translate_Z -= 0.001;
    //if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) scale_X += 0.001;
    //if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS) scale_X -= 0.001;
    //if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) scale_Y += 0.001;
    //if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) scale_Y -= 0.001;
    //if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) scale_Z += 0.001;
    //if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) scale_Z -= 0.001;

    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
    {
        rotateAngle_X += 0.1;
        rotateAxis_X = 1.0;
        rotateAxis_Y = 0.0;
        rotateAxis_Z = 0.0;
    }
    if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
    {
        rotateAngle_Y += 0.1;
        rotateAxis_X = 0.0;
        rotateAxis_Y = 1.0;
        rotateAxis_Z = 0.0;
    }
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
    {
        rotateAngle_Z += 0.1;
        rotateAxis_X = 0.0;
        rotateAxis_Y = 0.0;
        rotateAxis_Z = 1.0;
    }

}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{   ///////////////////////////////bishop's moves
    if (glfwGetKey(window, GLFW_KEY_K) && glfwGetKey(window, GLFW_KEY_RIGHT) && glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        xForBishop1 += 0.25f;
        xForBishop1Cube += 0.25f;
        zForBishop1 -= 0.25f;
        zForBishop1Cube -= 0.25f;
    }
    if (glfwGetKey(window, GLFW_KEY_K) && glfwGetKey(window, GLFW_KEY_F1) && glfwGetKey(window, GLFW_KEY_F2) == GLFW_PRESS)
    {
        xForBishop1 -= 0.25f;
        xForBishop1Cube -= 0.25f;
        zForBishop1 -= 0.25f;
        zForBishop1Cube -= 0.25f;
        cout << "debugging";
    }
    if (glfwGetKey(window, GLFW_KEY_K) && glfwGetKey(window, GLFW_KEY_RIGHT) && glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        xForBishop1 += 0.25f;
        xForBishop1Cube += 0.25f;
        zForBishop1 += 0.25f;
        zForBishop1Cube += 0.25f;
    }
    if (glfwGetKey(window, GLFW_KEY_K) && glfwGetKey(window, GLFW_KEY_F3) && glfwGetKey(window, GLFW_KEY_F4) == GLFW_PRESS)
    {
        xForBishop1 -= 0.25f;
        xForBishop1Cube -= 0.25f;
        zForBishop1 += 0.25f;
        zForBishop1Cube += 0.25f;
    }

    if (glfwGetKey(window, GLFW_KEY_L)&& glfwGetKey(window, GLFW_KEY_RIGHT) && glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        xForBishop2 += 0.25f;
        xForBishop2Cube += 0.25f;
        zForBishop2 -= 0.25f;
        zForBishop2Cube-= 0.25f;
    }
    if (glfwGetKey(window, GLFW_KEY_L) && glfwGetKey(window, GLFW_KEY_LEFT) && glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        xForBishop2 -= 0.25f;
        xForBishop2Cube -= 0.25f;
        zForBishop2 -= 0.25f;
        zForBishop2Cube -= 0.25f;
    }
    if (glfwGetKey(window, GLFW_KEY_L) && glfwGetKey(window, GLFW_KEY_RIGHT) && glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        xForBishop2 += 0.25f;
        xForBishop2Cube += 0.25f;
        zForBishop2 += 0.25f;
        zForBishop2Cube += 0.25f;
    }
    if (glfwGetKey(window, GLFW_KEY_L) && glfwGetKey(window, GLFW_KEY_LEFT) && glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        xForBishop2 -= 0.25f;
        xForBishop2Cube -= 0.25f;
        zForBishop2 += 0.25f;
        zForBishop2Cube += 0.25f;
    }
    if (glfwGetKey(window, GLFW_KEY_O) && glfwGetKey(window, GLFW_KEY_RIGHT) && glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        xForBishop3 += 0.25f;
        xForBishop3Cube += 0.25f;
        zForBishop3 -= 0.25f;
        zForBishop3Cube -= 0.25f;
    }
    if (glfwGetKey(window, GLFW_KEY_O) && glfwGetKey(window, GLFW_KEY_LEFT) && glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        xForBishop3 -= 0.25f;
        xForBishop3Cube -= 0.25f;
        zForBishop3 -= 0.25f;
        zForBishop3Cube -= 0.25f;
    }
    if (glfwGetKey(window, GLFW_KEY_O) && glfwGetKey(window, GLFW_KEY_RIGHT) && glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        xForBishop3 += 0.25f;
        xForBishop3Cube += 0.25f;
        zForBishop3 += 0.25f;
        zForBishop3Cube += 0.25f;
    }
    if (glfwGetKey(window, GLFW_KEY_O) && glfwGetKey(window, GLFW_KEY_LEFT) && glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        xForBishop3 -= 0.25f;
        xForBishop3Cube -= 0.25f;
        zForBishop3 += 0.25f;
        zForBishop3Cube += 0.25f;
    }


    if (glfwGetKey(window, GLFW_KEY_P) && glfwGetKey(window, GLFW_KEY_RIGHT) && glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        xForBishop4 += 0.25f;
        xForBishop4Cube += 0.25f;
        zForBishop4 -= 0.25f;
        zForBishop4Cube -= 0.25f;
    }
    if (glfwGetKey(window, GLFW_KEY_P) && glfwGetKey(window, GLFW_KEY_LEFT) && glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        xForBishop4 -= 0.25f;
        xForBishop4Cube -= 0.25f;
        zForBishop4 -= 0.25f;
        zForBishop4Cube -= 0.25f;
    }
    if (glfwGetKey(window, GLFW_KEY_P) && glfwGetKey(window, GLFW_KEY_RIGHT) && glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        xForBishop4 += 0.25f;
        xForBishop4Cube += 0.25f;
        zForBishop4 += 0.25f;
        zForBishop4Cube += 0.25f;
    }
    if (glfwGetKey(window, GLFW_KEY_P) && glfwGetKey(window, GLFW_KEY_LEFT) && glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        xForBishop4 -= 0.25f;
        xForBishop4Cube -= 0.25f;
        zForBishop4 += 0.25f;
        zForBishop4Cube += 0.25f;
    }
    if (glfwGetKey(window, GLFW_KEY_PRINT_SCREEN) == GLFW_PRESS)
    {
        if (!pressLforBishop1)
            pressLforBishop1 = true;

    }
    ///////////////////////////////pawn's moves
    if (glfwGetKey(window, GLFW_KEY_F1) && glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
       if(!pressForPawn1)
        pressForPawn1 = true;
   
 
    }
    if (glfwGetKey(window, GLFW_KEY_F2) && glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        if (!pressForPawn2)
            pressForPawn2= true;


    }
    if (glfwGetKey(window, GLFW_KEY_F3) && glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        if (!pressForPawn3)
            pressForPawn3= true;


    }
    if (glfwGetKey(window, GLFW_KEY_F4) && glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        if (!pressForPawn4)
            pressForPawn4= true;

    }
    if (glfwGetKey(window, GLFW_KEY_F5) && glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        if (!pressForPawn5)
            pressForPawn5= true;

    }
    if (glfwGetKey(window, GLFW_KEY_F6) && glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        if (!pressForPawn6)
            pressForPawn6= true;

    }

    if (glfwGetKey(window, GLFW_KEY_F6) && glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        if (!pressForPawn7)
            pressForPawn7 = true;

    }
    if (glfwGetKey(window, GLFW_KEY_F8) && glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        if (!pressForPawn8)
            pressForPawn8 = true;

    }
    if (glfwGetKey(window, GLFW_KEY_F9) && glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        if (!pressForPawn9)
            pressForPawn9 = true;

    }

    if (glfwGetKey(window, GLFW_KEY_F10) && glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        if (!pressForPawn10)
            pressForPawn10 = true;

    }   if (glfwGetKey(window, GLFW_KEY_F11) && glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        if (!pressForPawn11)
            pressForPawn11 = true;

    }   if (glfwGetKey(window, GLFW_KEY_F12) && glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        if (!pressForPawn12)
            pressForPawn12 = true;

    }
    ///////////////////////////////rook's moves
    if (glfwGetKey(window, GLFW_KEY_U) && glfwGetKey(window, GLFW_KEY_LEFT)  == GLFW_PRESS)
    {
        xforRook1 -= 0.25;

    }
    if (glfwGetKey(window, GLFW_KEY_U) && glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        xforRook1 += 0.25;

    }
    if (glfwGetKey(window, GLFW_KEY_U) && glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        zforRook1 -= 0.25;

    }
    if (glfwGetKey(window, GLFW_KEY_U) && glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        zforRook1 += 0.25;

    }


    if (glfwGetKey(window, GLFW_KEY_I) && glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        xforRook2 -= 0.25;

    }
    if (glfwGetKey(window, GLFW_KEY_I) && glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        xforRook2+= 0.25;

    }
    if (glfwGetKey(window, GLFW_KEY_I) && glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        zforRook2-= 0.25;

    }
    if (glfwGetKey(window, GLFW_KEY_I) && glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        zforRook2 += 0.25;

    }

    if (glfwGetKey(window, GLFW_KEY_H) && glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        xforRook3 -= 0.25;

    }
    if (glfwGetKey(window, GLFW_KEY_H) && glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        xforRook3+= 0.25;

    }
    if (glfwGetKey(window, GLFW_KEY_H) && glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        zforRook3 -= 0.25;

    }
    if (glfwGetKey(window, GLFW_KEY_H) && glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        zforRook3 += 0.25;

    }

    if (glfwGetKey(window, GLFW_KEY_J) && glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        xforRook4 -= 0.25;

    }
    if (glfwGetKey(window, GLFW_KEY_J) && glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        xforRook4 += 0.25;

    }
    if (glfwGetKey(window, GLFW_KEY_J) && glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        zforRook4 -= 0.25;

    }
    if (glfwGetKey(window, GLFW_KEY_J) && glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        zforRook4 += 0.25;

    }
    ////////////////////////////////king's moves
    if (glfwGetKey(window, GLFW_KEY_INSERT) && glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        zforKing1 -= 0.25;
        zForKing1Cube -= 0.25;

    }
    if (glfwGetKey(window, GLFW_KEY_INSERT) && glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        zforKing1 += 0.25;
        zForKing1Cube += 0.25;
    }
    if (glfwGetKey(window, GLFW_KEY_INSERT) && glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        xforKing1 -= 0.25;
        xForKing1Cube -= 0.25;
    }

    if (glfwGetKey(window, GLFW_KEY_INSERT) && glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        xforKing1 += 0.25;
        xForKing1Cube += 0.25;
    }

    if (glfwGetKey(window, GLFW_KEY_INSERT) && glfwGetKey(window, GLFW_KEY_F4) == GLFW_PRESS)
    {
        xforKing1 += 0.25;
        zforKing1 -= 0.25;
        xForKing1Cube += 0.25;
        zForKing1Cube -= 0.25;
    }
    if (glfwGetKey(window, GLFW_KEY_INSERT) && glfwGetKey(window, GLFW_KEY_F3) == GLFW_PRESS)
    {
        xforKing1 += 0.25;
        zforKing1 += 0.25;
        xForKing1Cube += 0.25;
        zForKing1Cube += 0.25;
    }

    if (glfwGetKey(window, GLFW_KEY_INSERT) && glfwGetKey(window, GLFW_KEY_F2) == GLFW_PRESS)
    {
        xforKing1 -= 0.25;
        zforKing1 += 0.25;
        xForKing1Cube -= 0.25;
        zForKing1Cube += 0.25;
    }

    if (glfwGetKey(window, GLFW_KEY_INSERT) && glfwGetKey(window, GLFW_KEY_F1) == GLFW_PRESS)
    {
        xforKing1 -= 0.25;
        zforKing1 -= 0.25;
        xForKing1Cube -= 0.25;
        zForKing1Cube -= 0.25;
    }

    if (glfwGetKey(window, GLFW_KEY_DELETE) && glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
       zforKing2 -= 0.25;
       zForKing2Cube -= 0.25;

    }
    if (glfwGetKey(window, GLFW_KEY_DELETE)  && glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        zforKing2 += 0.25;
        zForKing2Cube += 0.25;
    }
    if (glfwGetKey(window, GLFW_KEY_DELETE)  && glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        xforKing2 -= 0.25;
        xForKing2Cube -= 0.25;
    }

    if (glfwGetKey(window, GLFW_KEY_DELETE)  && glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        xforKing2 += 0.25;
        xForKing2Cube += 0.25;
    }

    if (glfwGetKey(window, GLFW_KEY_DELETE) && glfwGetKey(window, GLFW_KEY_F4) == GLFW_PRESS)
    {
        xforKing2 += 0.25;
        zforKing2 -= 0.25;
        xForKing2Cube += 0.25;
        zForKing2Cube -= 0.25;
    }
    if (glfwGetKey(window, GLFW_KEY_DELETE) && glfwGetKey(window, GLFW_KEY_F3) == GLFW_PRESS)
    {
        xforKing2 += 0.25;
        zforKing2 += 0.25;
        xForKing2Cube += 0.25;
        zForKing2Cube += 0.25;
    }

    if (glfwGetKey(window, GLFW_KEY_DELETE) && glfwGetKey(window, GLFW_KEY_F2) == GLFW_PRESS)
    {
        xforKing2 -= 0.25;
        zforKing2 += 0.25;
        xForKing2Cube -= 0.25;
        zForKing2Cube += 0.25;
    }

    if (glfwGetKey(window, GLFW_KEY_DELETE) && glfwGetKey(window, GLFW_KEY_F1)  == GLFW_PRESS)
    {
        xforKing2 -= 0.25;
        zforKing2 -= 0.25;
        xForKing2Cube -= 0.25;
        zForKing2Cube -= 0.25;
    }
    

    ///////queen's moves
    if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN) && glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)  
    {
        zforQueen2 -= 0.25;
   
    }
    if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN) && glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        zforQueen2 += 0.25;
    }
    if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN) && glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        xforQueen2 -= 0.25;
    }

    if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN) && glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        xforQueen2 += 0.25;
    }

    if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN) && glfwGetKey(window, GLFW_KEY_F4) == GLFW_PRESS)
    {
        
        xforQueen2 += 0.25;
        zforQueen2 -= 0.25;
      
    }
    if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN) && glfwGetKey(window, GLFW_KEY_F3) == GLFW_PRESS)
    {
        xforQueen2 += 0.25;
        zforQueen2 += 0.25;

    }

    if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN) && glfwGetKey(window, GLFW_KEY_F2) == GLFW_PRESS)
    {
        xforQueen2 -= 0.25;
        zforQueen2 += 0.25;

    }

    if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN) && glfwGetKey(window, GLFW_KEY_F1) == GLFW_PRESS)
    {
        xforQueen2 -= 0.25;
        zforQueen2 -= 0.25;
    }


    if (glfwGetKey(window, GLFW_KEY_PAGE_UP) && glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        zforQueen1 -= 0.25;

    }
    if (glfwGetKey(window, GLFW_KEY_PAGE_UP) && glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        zforQueen1 += 0.25;

    }
    if (glfwGetKey(window, GLFW_KEY_PAGE_UP) && glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        xforQueen1 -= 0.25;
    }

    if (glfwGetKey(window, GLFW_KEY_PAGE_UP) && glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        xforQueen1 += 0.25;

    }

    if (glfwGetKey(window, GLFW_KEY_PAGE_UP) && glfwGetKey(window, GLFW_KEY_F4) == GLFW_PRESS)
    {
        xforQueen1 += 0.25;
        zforQueen1 -= 0.25;

    }
    if (glfwGetKey(window, GLFW_KEY_PAGE_UP) && glfwGetKey(window, GLFW_KEY_F3) == GLFW_PRESS)
    {
        xforQueen1 += 0.25;
        zforQueen1 += 0.25;

    }

    if (glfwGetKey(window, GLFW_KEY_PAGE_UP) && glfwGetKey(window, GLFW_KEY_F2) == GLFW_PRESS)
    {
        xforQueen1 -= 0.25;
        zforQueen1 += 0.25;
  
    }

    if (glfwGetKey(window, GLFW_KEY_PAGE_UP) && glfwGetKey(window, GLFW_KEY_F1) == GLFW_PRESS)
    {
        xforQueen1 -= 0.25;
        zforQueen1 -= 0.25;

    }
   if (key == GLFW_KEY_1 && action == GLFW_PRESS)
    {
        if (pointLight1On)
        {
            pointlight1.turnOff();
            pointlight3.turnOff();
            
            pointLight1On = !pointLight1On;
            pointLight3On = !pointLight3On;
        }
        else
        {
            pointlight1.turnOn();
            pointlight3.turnOn();

            
            pointLight1On = !pointLight1On;
            pointLight3On = !pointLight3On;
        }
    }
   if (key == GLFW_KEY_2 && action == GLFW_PRESS)
   {
       if (pointLight2On)
       {
           pointlight2.turnOff();
           pointlight4.turnOff();

           pointLight2On = !pointLight2On;
           pointLight4On = !pointLight4On;
       }
       else
       {

           pointlight2.turnOn();
           pointlight4.turnOn();

           pointLight2On = !pointLight2On;
           pointLight4On = !pointLight4On;
       }
   }
    if (key == GLFW_KEY_3 && action == GLFW_PRESS)
    {
        if (directionalLightOn)
        {
            directionalLight.turnOff();

            directionalLightOn = !directionalLightOn;
        }
        else
        {
            directionalLight.turnOn();

            directionalLightOn = !directionalLightOn;
        }
    }
    if (key == GLFW_KEY_4 && action == GLFW_PRESS)
    {
        if (spotLightOn)
        {
            //spotLight1.turnOff();
            spotLight2.turnOff();

            spotLightOn = !spotLightOn;
        }
        else
        {
            //spotLight1.turnOn();
            spotLight2.turnOn();
            spotLightOn = !spotLightOn;
        }
    }


    else if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS)
    {
        if (specularToggle)
        {

            pointlight1.turnSpecularOff();
            pointlight2.turnSpecularOff();
         
            directionalLight.turnSpecularOff();
            //spotLight1.turnSpecularOff();
            spotLight2.turnSpecularOff();
            specularToggle = !specularToggle;
        }
        else
        {

            pointlight1.turnSpecularOn();
            pointlight2.turnSpecularOn();
          
            directionalLight.turnSpecularOn();
            //spotLight1.turnSpecularOn();
            spotLight2.turnSpecularOn();
            specularToggle = !specularToggle;
        }
    }

    else if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)
    {
        if (diffuseToggle)
        {

            pointlight1.turnDiffuseOff();
            pointlight2.turnDiffuseOff();
          
            directionalLight.turnDiffuseOff();
            //spotLight1.turnDiffuseOff();
            spotLight2.turnDiffuseOff();
            diffuseToggle = !diffuseToggle;
        }
        else
        {

            pointlight1.turnDiffuseOn();
            pointlight2.turnDiffuseOn();
            
            directionalLight.turnDiffuseOn();
            //spotLight1.turnDiffuseOn();
            spotLight2.turnDiffuseOn();
            diffuseToggle = !diffuseToggle;
        }
    }

    else if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
    {
        if (ambientToggle)
        {

            pointlight1.turnAmbientOff();
            pointlight2.turnAmbientOff();
            
            directionalLight.turnAmbientOff();
            //spotLight1.turnAmbientOff();
            spotLight2.turnAmbientOff();
            ambientToggle = !ambientToggle;
        }
        else
        {

            pointlight1.turnAmbientOn();
            pointlight2.turnAmbientOn();
          
            directionalLight.turnAmbientOn();
            //spotLight1.turnAmbientOn();
            spotLight2.turnAmbientOn();
            ambientToggle = !ambientToggle;
        }
    }
   
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = ypos- lastY ; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}
unsigned int loadTexture(char const* path, GLenum textureWrappingModeS, GLenum textureWrappingModeT, GLenum textureFilteringModeMin, GLenum textureFilteringModeMax)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, textureWrappingModeS);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, textureWrappingModeT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, textureFilteringModeMin);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, textureFilteringModeMax);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}


long long nCr(int n, int r)
{
    if (r > n / 2)
        r = n - r; // because C(n, r) == C(n, n - r)
    long long ans = 1;
    int i;

    for (i = 1; i <= r; i++)
    {
        ans *= n - r + i;
        ans /= i;
    }

    return ans;
}

//polynomial interpretation for N points
void BezierCurve(double t, float xy[2], GLfloat ctrlpoints[], int L)
{
    double y = 0;
    double x = 0;
    t = t > 1.0 ? 1.0 : t;
    for (int i = 0; i < L + 1; i++)
    {
        long long ncr = nCr(L, i);
        double oneMinusTpow = pow(1 - t, double(L - i));
        double tPow = pow(t, double(i));
        double coef = oneMinusTpow * tPow * ncr;
        x += coef * ctrlpoints[i * 3];
        y += coef * ctrlpoints[(i * 3) + 1];

    }
    xy[0] = float(x);
    xy[1] = float(y);
}

unsigned int hollowBezier(GLfloat ctrlpoints[], int L)
{
    int i, j;
    float x, y, z, r;                //current coordinates
    float theta;
    float nx, ny, nz, lengthInv;    // vertex normal

    coordinates.clear();
    normals.clear();
    indices.clear();

    const float dtheta = 2 * pi / ntheta;        //angular step size

    float t = 0;
    float dt = 1.0 / nt;
    float xy[2];

    for (i = 0; i <= nt; ++i)              //step through y
    {
        BezierCurve(t, xy, ctrlpoints, L);
        r = xy[0];
        y = xy[1];
        theta = 0;
        t += dt;
        lengthInv = 1.0 / r;

        for (j = 0; j <= ntheta; ++j)
        {
            double cosa = cos(theta);
            double sina = sin(theta);
            z = r * cosa;
            x = r * sina;

            coordinates.push_back(x);
            coordinates.push_back(y);
            coordinates.push_back(z);

            // normalized vertex normal (nx, ny, nz)
            // center point of the circle (0,y,0)
            nx = (x - 0) * lengthInv;
            ny = (y - y) * lengthInv;
            nz = (z - 0) * lengthInv;

            normals.push_back(nx);
            normals.push_back(ny);
            normals.push_back(nz);

            theta += dtheta;
        }
    }

    int k1, k2;
    for (int i = 0; i < nt; ++i)
    {
        k1 = i * (ntheta + 1);     // beginning of current stack
        k2 = k1 + ntheta + 1;      // beginning of next stack

        for (int j = 0; j < ntheta; ++j, ++k1, ++k2)
        {
            // k1 => k2 => k1+1
            indices.push_back(k1);
            indices.push_back(k2);
            indices.push_back(k1 + 1);

            // k1+1 => k2 => k2+1
            indices.push_back(k1 + 1);
            indices.push_back(k2);
            indices.push_back(k2 + 1);
        }
    }

    size_t count = coordinates.size();
    for (int i = 0; i < count; i += 3)
    {
        vertices.push_back(coordinates[i]);
        vertices.push_back(coordinates[i + 1]);
        vertices.push_back(coordinates[i + 2]);

        vertices.push_back(normals[i]);
        vertices.push_back(normals[i + 1]);
        vertices.push_back(normals[i + 2]);
    }

    unsigned int bezierVAO;
    glGenVertexArrays(1, &bezierVAO);
    glBindVertexArray(bezierVAO);

    // create VBO to copy vertex data to VBO
    unsigned int bezierVBO;
    glGenBuffers(1, &bezierVBO);
    glBindBuffer(GL_ARRAY_BUFFER, bezierVBO);           // for vertex data
    glBufferData(GL_ARRAY_BUFFER,                   // target
        (unsigned int)vertices.size() * sizeof(float), // data size, # of bytes
        vertices.data(),   // ptr to vertex data
        GL_STATIC_DRAW);                   // usage

    // create EBO to copy index data
    unsigned int bezierEBO;
    glGenBuffers(1, &bezierEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bezierEBO);   // for index data
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,           // target
        (unsigned int)indices.size() * sizeof(unsigned int),             // data size, # of bytes
        indices.data(),               // ptr to index data
        GL_STATIC_DRAW);                   // usage

    // activate attrib arrays
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    // set attrib arrays with stride and offset
    int stride = 24;     // should be 24 bytes
    glVertexAttribPointer(0, 3, GL_FLOAT, false, stride, (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, false, stride, (void*)(sizeof(float) * 3));

    // unbind VAO, VBO and EBO
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    return bezierVAO;
}


void pawn2(unsigned int& bezierVAO, unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether, float cube_x, float cube_y, float cube_z,
    float cube_height, float cube_w, float cube_b, float sphere_x, float sphere_y, float sphere_z, float sphere_height, float sphere_w,
    float sphere_b, float r, float g, float b) {

    glm::mat4 modelforPawn = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    glm::mat4 rotate = glm::mat4(1.0f);
    translate = glm::translate(modelforPawn, glm::vec3(cube_x + 0.0625, cube_y, cube_z + 0.0675));
    scale = glm::scale(modelforPawn, glm::vec3(0.07, 0.12f, 0.07));
    modelforPawn = alTogether * translate * scale;
    drawCurve(bezierVAO, lightingShader, modelforPawn, r, g, b);

    modelforPawn = glm::mat4(1.0f);
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    modelforPawn = alTogether * translate * scale;
    drawSphere(lightingShader, alTogether * modelforPawn, sphere_x, sphere_y + 0.025, sphere_z, sphere_height, sphere_w, sphere_b, 1.0, 1.0, 1.0);

    modelforPawn = glm::mat4(1.0f);
    identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    modelforPawn = alTogether * translate * scale;
    drawSphere(lightingShader, alTogether * modelforPawn, sphere_x, sphere_y - 0.205f, sphere_z, 0.10f, 0.050f, 0.10f, 1.0, 1.0, 1.0);

    modelforPawn = glm::mat4(1.0f);
    identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    modelforPawn = alTogether * translate * scale;
    drawSphere(lightingShader, alTogether * modelforPawn, sphere_x, sphere_y - 0.015, sphere_z, 0.08f, 0.025f, 0.08f, 1.0, 1.0, 1.0);

}
void pawn3(unsigned int& bezierVAO, unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether, float cube_x, float cube_y, float cube_z,
    float cube_height, float cube_w, float cube_b, float sphere_x, float sphere_y, float sphere_z, float sphere_height, float sphere_w,
    float sphere_b, float r, float g, float b) {

    glm::mat4 modelforPawn = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    glm::mat4 rotate = glm::mat4(1.0f);
    translate = glm::translate(modelforPawn, glm::vec3(cube_x + 0.0625, cube_y, cube_z + 0.0675));
    scale = glm::scale(modelforPawn, glm::vec3(0.07, 0.12f, 0.07));
    modelforPawn = alTogether * translate * scale;
    drawCurve(bezierVAO, lightingShader, modelforPawn, r, g, b);

    modelforPawn = glm::mat4(1.0f);
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    modelforPawn = alTogether * translate * scale;
    drawSphere(lightingShader, alTogether * modelforPawn, sphere_x, sphere_y + 0.025, sphere_z, sphere_height, sphere_w, sphere_b, 1.0, 1.0, 1.0);

    modelforPawn = glm::mat4(1.0f);
    identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    modelforPawn = alTogether * translate * scale;
    drawSphere(lightingShader, alTogether * modelforPawn, sphere_x, sphere_y - 0.205f, sphere_z, 0.10f, 0.050f, 0.10f, 1.0, 1.0, 1.0);

    modelforPawn = glm::mat4(1.0f);
    identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    modelforPawn = alTogether * translate * scale;
    drawSphere(lightingShader, alTogether * modelforPawn, sphere_x, sphere_y - 0.015, sphere_z, 0.08f, 0.025f, 0.08f, 1.0, 1.0, 1.0);

}
void pawn4(unsigned int& bezierVAO, unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether, float cube_x, float cube_y, float cube_z,
    float cube_height, float cube_w, float cube_b, float sphere_x, float sphere_y, float sphere_z, float sphere_height, float sphere_w,
    float sphere_b, float r, float g, float b) {

    glm::mat4 modelforPawn = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    glm::mat4 rotate = glm::mat4(1.0f);
    translate = glm::translate(modelforPawn, glm::vec3(cube_x + 0.0625, cube_y, cube_z + 0.0675));
    scale = glm::scale(modelforPawn, glm::vec3(0.07, 0.12f, 0.07));
    modelforPawn = alTogether * translate * scale;
    drawCurve(bezierVAO, lightingShader, modelforPawn, r, g, b);

    modelforPawn = glm::mat4(1.0f);
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    modelforPawn = alTogether * translate * scale;
    drawSphere(lightingShader, alTogether * modelforPawn, sphere_x, sphere_y + 0.025, sphere_z, sphere_height, sphere_w, sphere_b, 1.0, 1.0, 1.0);

    modelforPawn = glm::mat4(1.0f);
    identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    modelforPawn = alTogether * translate * scale;
    drawSphere(lightingShader, alTogether * modelforPawn, sphere_x, sphere_y - 0.205f, sphere_z, 0.10f, 0.050f, 0.10f, 1.0, 1.0, 1.0);

    modelforPawn = glm::mat4(1.0f);
    identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    modelforPawn = alTogether * translate * scale;
    drawSphere(lightingShader, alTogether * modelforPawn, sphere_x, sphere_y - 0.015, sphere_z, 0.08f, 0.025f, 0.08f, 1.0, 1.0, 1.0);

}
void pawn5(unsigned int& bezierVAO, unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether, float cube_x, float cube_y, float cube_z,
    float cube_height, float cube_w, float cube_b, float sphere_x, float sphere_y, float sphere_z, float sphere_height, float sphere_w,
    float sphere_b, float r, float g, float b) {

    glm::mat4 modelforPawn = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    glm::mat4 rotate = glm::mat4(1.0f);
    translate = glm::translate(modelforPawn, glm::vec3(cube_x + 0.0625, cube_y, cube_z + 0.0675));
    scale = glm::scale(modelforPawn, glm::vec3(0.07, 0.12f, 0.07));
    modelforPawn = alTogether * translate * scale;
    drawCurve(bezierVAO, lightingShader, modelforPawn, r, g, b);

    modelforPawn = glm::mat4(1.0f);
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    modelforPawn = alTogether * translate * scale;
    drawSphere(lightingShader, alTogether * modelforPawn, sphere_x, sphere_y + 0.025, sphere_z, sphere_height, sphere_w, sphere_b, 1.0, 1.0, 1.0);

    modelforPawn = glm::mat4(1.0f);
    identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    modelforPawn = alTogether * translate * scale;
    drawSphere(lightingShader, alTogether * modelforPawn, sphere_x, sphere_y - 0.205f, sphere_z, 0.10f, 0.050f, 0.10f, 1.0, 1.0, 1.0);

    modelforPawn = glm::mat4(1.0f);
    identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    modelforPawn = alTogether * translate * scale;
    drawSphere(lightingShader, alTogether * modelforPawn, sphere_x, sphere_y - 0.015, sphere_z, 0.08f, 0.025f, 0.08f, 1.0, 1.0, 1.0);

}
void pawn6(unsigned int& bezierVAO, unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether, float cube_x, float cube_y, float cube_z,
    float cube_height, float cube_w, float cube_b, float sphere_x, float sphere_y, float sphere_z, float sphere_height, float sphere_w,
    float sphere_b, float r, float g, float b) {

    glm::mat4 modelforPawn = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    glm::mat4 rotate = glm::mat4(1.0f);
    translate = glm::translate(modelforPawn, glm::vec3(cube_x + 0.0625, cube_y, cube_z + 0.0675));
    scale = glm::scale(modelforPawn, glm::vec3(0.07, 0.12f, 0.07));
    modelforPawn = alTogether * translate * scale;
    drawCurve(bezierVAO, lightingShader, modelforPawn, r, g, b);

    modelforPawn = glm::mat4(1.0f);
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    modelforPawn = alTogether * translate * scale;
    drawSphere(lightingShader, alTogether * modelforPawn, sphere_x, sphere_y + 0.025, sphere_z, sphere_height, sphere_w, sphere_b, 1.0, 1.0, 1.0);

    modelforPawn = glm::mat4(1.0f);
    identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    modelforPawn = alTogether * translate * scale;
    drawSphere(lightingShader, alTogether * modelforPawn, sphere_x, sphere_y - 0.205f, sphere_z, 0.10f, 0.050f, 0.10f, 1.0, 1.0, 1.0);

    modelforPawn = glm::mat4(1.0f);
    identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    modelforPawn = alTogether * translate * scale;
    drawSphere(lightingShader, alTogether * modelforPawn, sphere_x, sphere_y - 0.015, sphere_z, 0.08f, 0.025f, 0.08f, 1.0, 1.0, 1.0);

}
void pawn7(unsigned int& bezierVAO, unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether, float cube_x, float cube_y, float cube_z,
    float cube_height, float cube_w, float cube_b, float sphere_x, float sphere_y, float sphere_z, float sphere_height, float sphere_w,
    float sphere_b, float r, float g, float b) {

    glm::mat4 modelforPawn = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    glm::mat4 rotate = glm::mat4(1.0f);
    translate = glm::translate(modelforPawn, glm::vec3(cube_x + 0.0625, cube_y, cube_z + 0.0675));
    scale = glm::scale(modelforPawn, glm::vec3(0.07, 0.12f, 0.07));
    modelforPawn = alTogether * translate * scale;
    drawCurve(bezierVAO, lightingShader, modelforPawn, r, g, b);

    modelforPawn = glm::mat4(1.0f);
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    modelforPawn = alTogether * translate * scale;
    drawSphere(lightingShader, alTogether * modelforPawn, sphere_x, sphere_y + 0.025, sphere_z, sphere_height, sphere_w, sphere_b, r, g, b);

    modelforPawn = glm::mat4(1.0f);
    identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    modelforPawn = alTogether * translate * scale;
    drawSphere(lightingShader, alTogether * modelforPawn, sphere_x, sphere_y - 0.205f, sphere_z, 0.10f, 0.050f, 0.10f, r, g, b);

    modelforPawn = glm::mat4(1.0f);
    identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    modelforPawn = alTogether * translate * scale;
    drawSphere(lightingShader, alTogether * modelforPawn, sphere_x, sphere_y - 0.015, sphere_z, 0.08f, 0.025f, 0.08f, r, g, b);

}
void pawn8(unsigned int& bezierVAO, unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether, float cube_x, float cube_y, float cube_z,
    float cube_height, float cube_w, float cube_b, float sphere_x, float sphere_y, float sphere_z, float sphere_height, float sphere_w,
    float sphere_b, float r, float g, float b) {

    glm::mat4 modelforPawn = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    glm::mat4 rotate = glm::mat4(1.0f);
    translate = glm::translate(modelforPawn, glm::vec3(cube_x + 0.0625, cube_y, cube_z + 0.0675));
    scale = glm::scale(modelforPawn, glm::vec3(0.07, 0.12f, 0.07));
    modelforPawn = alTogether * translate * scale;
    drawCurve(bezierVAO, lightingShader, modelforPawn, r, g, b);

    modelforPawn = glm::mat4(1.0f);
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    modelforPawn = alTogether * translate * scale;
    drawSphere(lightingShader, alTogether * modelforPawn, sphere_x, sphere_y + 0.025, sphere_z, sphere_height, sphere_w, sphere_b, r, g, b);

    modelforPawn = glm::mat4(1.0f);
    identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    modelforPawn = alTogether * translate * scale;
    drawSphere(lightingShader, alTogether * modelforPawn, sphere_x, sphere_y - 0.205f, sphere_z, 0.10f, 0.050f, 0.10f, r, g, b);

    modelforPawn = glm::mat4(1.0f);
    identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    modelforPawn = alTogether * translate * scale;
    drawSphere(lightingShader, alTogether * modelforPawn, sphere_x, sphere_y - 0.015, sphere_z, 0.08f, 0.025f, 0.08f, r, g, b);

}
void pawn9(unsigned int& bezierVAO, unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether, float cube_x, float cube_y, float cube_z,
    float cube_height, float cube_w, float cube_b, float sphere_x, float sphere_y, float sphere_z, float sphere_height, float sphere_w,
    float sphere_b, float r, float g, float b) {

    glm::mat4 modelforPawn = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    glm::mat4 rotate = glm::mat4(1.0f);
    translate = glm::translate(modelforPawn, glm::vec3(cube_x + 0.0625, cube_y, cube_z + 0.0675));
    scale = glm::scale(modelforPawn, glm::vec3(0.07, 0.12f, 0.07));
    modelforPawn = alTogether * translate * scale;
    drawCurve(bezierVAO, lightingShader, modelforPawn, r, g, b);

    modelforPawn = glm::mat4(1.0f);
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    modelforPawn = alTogether * translate * scale;
    drawSphere(lightingShader, alTogether * modelforPawn, sphere_x, sphere_y + 0.025, sphere_z, sphere_height, sphere_w, sphere_b, r, g, b);

    modelforPawn = glm::mat4(1.0f);
    identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    modelforPawn = alTogether * translate * scale;
    drawSphere(lightingShader, alTogether * modelforPawn, sphere_x, sphere_y - 0.205f, sphere_z, 0.10f, 0.050f, 0.10f, r, g, b);

    modelforPawn = glm::mat4(1.0f);
    identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    modelforPawn = alTogether * translate * scale;
    drawSphere(lightingShader, alTogether * modelforPawn, sphere_x, sphere_y - 0.015, sphere_z, 0.08f, 0.025f, 0.08f, r, g, b);

}
void pawn10(unsigned int& bezierVAO, unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether, float cube_x, float cube_y, float cube_z,
    float cube_height, float cube_w, float cube_b, float sphere_x, float sphere_y, float sphere_z, float sphere_height, float sphere_w,
    float sphere_b, float r, float g, float b) {

    glm::mat4 modelforPawn = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    glm::mat4 rotate = glm::mat4(1.0f);
    translate = glm::translate(modelforPawn, glm::vec3(cube_x + 0.0625, cube_y, cube_z + 0.0675));
    scale = glm::scale(modelforPawn, glm::vec3(0.07, 0.12f, 0.07));
    modelforPawn = alTogether * translate * scale;
    drawCurve(bezierVAO, lightingShader, modelforPawn, r, g, b);

    modelforPawn = glm::mat4(1.0f);
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    modelforPawn = alTogether * translate * scale;
    drawSphere(lightingShader, alTogether * modelforPawn, sphere_x, sphere_y + 0.025, sphere_z, sphere_height, sphere_w, sphere_b, r, g, b);

    modelforPawn = glm::mat4(1.0f);
    identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    modelforPawn = alTogether * translate * scale;
    drawSphere(lightingShader, alTogether * modelforPawn, sphere_x, sphere_y - 0.205f, sphere_z, 0.10f, 0.050f, 0.10f, r, g, b);

    modelforPawn = glm::mat4(1.0f);
    identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    modelforPawn = alTogether * translate * scale;
    drawSphere(lightingShader, alTogether * modelforPawn, sphere_x, sphere_y - 0.015, sphere_z, 0.08f, 0.025f, 0.08f, r, g, b);

}
void pawn11(unsigned int& bezierVAO, unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether, float cube_x, float cube_y, float cube_z,
    float cube_height, float cube_w, float cube_b, float sphere_x, float sphere_y, float sphere_z, float sphere_height, float sphere_w,
    float sphere_b, float r, float g, float b) {

    glm::mat4 modelforPawn = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    glm::mat4 rotate = glm::mat4(1.0f);
    translate = glm::translate(modelforPawn, glm::vec3(cube_x + 0.0625, cube_y, cube_z + 0.0675));
    scale = glm::scale(modelforPawn, glm::vec3(0.07, 0.12f, 0.07));
    modelforPawn = alTogether * translate * scale;
    drawCurve(bezierVAO, lightingShader, modelforPawn, r, g, b);

    modelforPawn = glm::mat4(1.0f);
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    modelforPawn = alTogether * translate * scale;
    drawSphere(lightingShader, alTogether * modelforPawn, sphere_x, sphere_y + 0.025, sphere_z, sphere_height, sphere_w, sphere_b, r, g, b);

    modelforPawn = glm::mat4(1.0f);
    identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    modelforPawn = alTogether * translate * scale;
    drawSphere(lightingShader, alTogether * modelforPawn, sphere_x, sphere_y - 0.205f, sphere_z, 0.10f, 0.050f, 0.10f, r, g, b);

    modelforPawn = glm::mat4(1.0f);
    identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    modelforPawn = alTogether * translate * scale;
    drawSphere(lightingShader, alTogether * modelforPawn, sphere_x, sphere_y - 0.015, sphere_z, 0.08f, 0.025f, 0.08f, r, g, b);

}
void pawn12(unsigned int& bezierVAO, unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether, float cube_x, float cube_y, float cube_z,
    float cube_height, float cube_w, float cube_b, float sphere_x, float sphere_y, float sphere_z, float sphere_height, float sphere_w,
    float sphere_b, float r, float g, float b) {

    glm::mat4 modelforPawn = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    glm::mat4 rotate = glm::mat4(1.0f);
    translate = glm::translate(modelforPawn, glm::vec3(cube_x + 0.0625, cube_y, cube_z + 0.0675));
    scale = glm::scale(modelforPawn, glm::vec3(0.07, 0.12f, 0.07));
    modelforPawn = alTogether * translate * scale;
    drawCurve(bezierVAO, lightingShader, modelforPawn, r, g, b);

    modelforPawn = glm::mat4(1.0f);
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    modelforPawn = alTogether * translate * scale;
    drawSphere(lightingShader, alTogether * modelforPawn, sphere_x, sphere_y + 0.025, sphere_z, sphere_height, sphere_w, sphere_b, r, g, b);

    modelforPawn = glm::mat4(1.0f);
    identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    modelforPawn = alTogether * translate * scale;
    drawSphere(lightingShader, alTogether * modelforPawn, sphere_x, sphere_y - 0.205f, sphere_z, 0.10f, 0.050f, 0.10f, r, g, b);

    modelforPawn = glm::mat4(1.0f);
    identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    modelforPawn = alTogether * translate * scale;
    drawSphere(lightingShader, alTogether * modelforPawn, sphere_x, sphere_y - 0.015, sphere_z, 0.08f, 0.025f, 0.08f, r, g, b);

}

void bishop2(unsigned int& bezierVAO, unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether, float x, float y, float z, float h, float w,
    float b, float r, float g, float bl, float cube_x, float cube_y, float cube_z) {

    glm::mat4 modelForBishop = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    glm::mat4 rotate = glm::mat4(1.0f);
    translate = glm::translate(modelForBishop, glm::vec3(x - 0.01f, y + 0.055, z));
    scale = glm::scale(modelForBishop, glm::vec3(h, w, b));
    modelForBishop = alTogether * translate * scale;
    drawCurve(bezierVAO, lightingShader, modelForBishop, r, g, bl);

    modelForBishop = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    rotate = glm::mat4(1.0f);
    modelForBishop = alTogether * translate * scale;
    drawSphere(lightingShader, alTogether * modelForBishop, x - 0.01f, y + 0.165f, z, 0.0365f, 0.0365f, 0.0365f, r, g, bl);

    modelForBishop = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    rotate = glm::mat4(1.0f);
    modelForBishop = alTogether * translate * scale;
    drawSphere(lightingShader, alTogether * modelForBishop, x, y - 0.105f, z - 0.01f, 0.2f, 0.01f, 0.2f, r, g, bl);

    modelForBishop = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    rotate = glm::mat4(1.0f);
    modelForBishop = alTogether * translate * scale;
    drawSphere(lightingShader, alTogether * modelForBishop, x - 0.01, y + 0.085f, z, 0.15f, 0.05f, 0.15f, r, g, bl);

    modelForBishop = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    rotate = glm::mat4(1.0f);
    translate = glm::translate(modelForBishop, glm::vec3(cube_x, cube_y, cube_z));
    scale = glm::scale(modelForBishop, glm::vec3(0.10f, 0.25f, 0.10f));
    modelForBishop = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, alTogether * modelForBishop, r, g, bl);

}
void bishop3(unsigned int& bezierVAO, unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether, float x, float y, float z, float h, float w,
    float b, float r, float g, float bl, float cube_x, float cube_y, float cube_z) {

    glm::mat4 modelForBishop = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    glm::mat4 rotate = glm::mat4(1.0f);
    translate = glm::translate(modelForBishop, glm::vec3(x - 0.01f, y + 0.055, z));
    scale = glm::scale(modelForBishop, glm::vec3(h, w, b));
    modelForBishop = alTogether * translate * scale;
    drawCurve(bezierVAO, lightingShader, modelForBishop, r, g, bl);

    modelForBishop = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    rotate = glm::mat4(1.0f);
    modelForBishop = alTogether * translate * scale;
    drawSphere(lightingShader, alTogether * modelForBishop, x - 0.01f, y + 0.165f, z, 0.0365f, 0.0365f, 0.0365f, r, g, bl);

    modelForBishop = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    rotate = glm::mat4(1.0f);
    modelForBishop = alTogether * translate * scale;
    drawSphere(lightingShader, alTogether * modelForBishop, x, y - 0.105f, z - 0.01f, 0.2f, 0.01f, 0.2f, r, g, bl);

    modelForBishop = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    rotate = glm::mat4(1.0f);
    modelForBishop = alTogether * translate * scale;
    drawSphere(lightingShader, alTogether * modelForBishop, x - 0.01, y + 0.085f, z, 0.15f, 0.05f, 0.15f, r, g, bl);

    modelForBishop = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    rotate = glm::mat4(1.0f);
    translate = glm::translate(modelForBishop, glm::vec3(cube_x, cube_y, cube_z));
    scale = glm::scale(modelForBishop, glm::vec3(0.10f, 0.25f, 0.10f));
    modelForBishop = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, alTogether * modelForBishop, r, g, bl);

}
void bishop4(unsigned int& bezierVAO, unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether, float x, float y, float z, float h, float w,
    float b, float r, float g, float bl, float cube_x, float cube_y, float cube_z) {

    glm::mat4 modelForBishop = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    glm::mat4 rotate = glm::mat4(1.0f);
    translate = glm::translate(modelForBishop, glm::vec3(x - 0.01f, y + 0.055, z));
    scale = glm::scale(modelForBishop, glm::vec3(h, w, b));
    modelForBishop = alTogether * translate * scale;
    drawCurve(bezierVAO, lightingShader, modelForBishop, r, g, bl);

    modelForBishop = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    rotate = glm::mat4(1.0f);
    modelForBishop = alTogether * translate * scale;
    drawSphere(lightingShader, alTogether * modelForBishop, x - 0.01f, y + 0.165f, z, 0.0365f, 0.0365f, 0.0365f, r, g, bl);

    modelForBishop = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    rotate = glm::mat4(1.0f);
    modelForBishop = alTogether * translate * scale;
    drawSphere(lightingShader, alTogether * modelForBishop, x, y - 0.105f, z - 0.01f, 0.2f, 0.01f, 0.2f, r, g, bl);

    modelForBishop = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    rotate = glm::mat4(1.0f);
    modelForBishop = alTogether * translate * scale;
    drawSphere(lightingShader, alTogether * modelForBishop, x - 0.01, y + 0.085f, z, 0.15f, 0.05f, 0.15f, r, g, bl);

    modelForBishop = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    rotate = glm::mat4(1.0f);
    translate = glm::translate(modelForBishop, glm::vec3(cube_x, cube_y, cube_z));
    scale = glm::scale(modelForBishop, glm::vec3(0.10f, 0.25f, 0.10f));
    modelForBishop = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, alTogether * modelForBishop, r, g, bl);

}
void rook1(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether, float cube_x, float cube_y, float cube_z,
    float cube_height, float cube_w, float cube_b, float r, float g, float b) {

    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translate, scale, modelForPawn;
    glm::mat4 rotate;
    rotate = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
    translate = glm::translate(identityMatrix, glm::vec3(cube_x + 0.05, cube_y + 0.40, cube_z + 0.75));
    scale = glm::scale(identityMatrix, glm::vec3(cube_height, cube_w, cube_b));
    modelForPawn = alTogether * translate * scale;
    lightingShader.setMat4("model", modelForPawn);

    drawCube(cubeVAO, lightingShader, alTogether * modelForPawn, r, g, b);

    identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::translate(identityMatrix, glm::vec3(cube_x + 0.08, cube_y + 0.5, cube_z + 0.75));
    scale = glm::scale(identityMatrix, glm::vec3(cube_height - 0.055, cube_w + 0.025, cube_b));
    modelForPawn = alTogether * translate * scale;

    lightingShader.setMat4("model", modelForPawn);

    drawCube(cubeVAO, lightingShader, alTogether * modelForPawn, r, g, b);

    identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::translate(identityMatrix, glm::vec3(cube_x + 0.065, cube_y + 0.6, cube_z + 0.725));
    scale = glm::scale(identityMatrix, glm::vec3(cube_height - 0.025, cube_w - 0.05, cube_b + 0.05));
    modelForPawn = alTogether * translate * scale;

    lightingShader.setMat4("model", modelForPawn);

    drawCube(cubeVAO, lightingShader, alTogether * modelForPawn, r, g, b);
    identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::translate(identityMatrix, glm::vec3(cube_x + 0.065, cube_y + 0.65, cube_z + 0.725));
    scale = glm::scale(identityMatrix, glm::vec3(cube_height - 0.14, cube_w - 0.07, cube_b + 0.05));
    modelForPawn = alTogether * translate * scale;

    lightingShader.setMat4("model", modelForPawn);

    drawCube(cubeVAO, lightingShader, alTogether * modelForPawn, r, g, b);

    identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::translate(identityMatrix, glm::vec3(cube_x + 0.065, cube_y + 0.68, cube_z + 0.725));
    scale = glm::scale(identityMatrix, glm::vec3(cube_height - 0.14, cube_w - 0.07, cube_b - 0.06));
    modelForPawn = alTogether * translate * scale;

    lightingShader.setMat4("model", modelForPawn);

    drawCube(cubeVAO, lightingShader, alTogether * modelForPawn, r, g, b);

    identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::translate(identityMatrix, glm::vec3(cube_x + 0.065, cube_y + 0.68, cube_z + 0.86 - 0.025));
    scale = glm::scale(identityMatrix, glm::vec3(cube_height - 0.14, cube_w - 0.07, cube_b - 0.06));
    modelForPawn = alTogether * translate * scale;

    lightingShader.setMat4("model", modelForPawn);

    drawCube(cubeVAO, lightingShader, alTogether * modelForPawn, r, g, b);


    identityMatrix = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::translate(identityMatrix, glm::vec3(cube_x + 0.065 + .115, cube_y + 0.65, cube_z + 0.725));
    scale = glm::scale(identityMatrix, glm::vec3(cube_height - 0.14, cube_w - 0.07, cube_b + 0.05));
    modelForPawn = alTogether * translate * scale;

    lightingShader.setMat4("model", modelForPawn);

    drawCube(cubeVAO, lightingShader, alTogether * modelForPawn, r, g, b);

    identityMatrix = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::translate(identityMatrix, glm::vec3(cube_x + 0.065 + .115, cube_y + 0.68, cube_z + 0.725));
    scale = glm::scale(identityMatrix, glm::vec3(cube_height - 0.14, cube_w - 0.07, cube_b - 0.06));
    modelForPawn = alTogether * translate * scale;

    lightingShader.setMat4("model", modelForPawn);

    drawCube(cubeVAO, lightingShader, alTogether * modelForPawn, r, g, b);

    identityMatrix = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::translate(identityMatrix, glm::vec3(cube_x + 0.065 + .115, cube_y + 0.68, cube_z + 0.86 - 0.025));
    scale = glm::scale(identityMatrix, glm::vec3(cube_height - 0.14, cube_w - 0.07, cube_b - 0.06));
    modelForPawn = alTogether * translate * scale;

    lightingShader.setMat4("model", modelForPawn);

    drawCube(cubeVAO, lightingShader, alTogether * modelForPawn, r, g, b);

    identityMatrix = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);

    translate = glm::translate(identityMatrix, glm::vec3(cube_x + 0.070, cube_y + .65, cube_z + 0.725));
    scale = glm::scale(identityMatrix, glm::vec3(cube_height - 0.14, cube_w - 0.07, cube_b + 0.02));
    rotate = glm::mat4(1.0f);
    rotate = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    modelForPawn = alTogether * translate * rotate * scale;

    lightingShader.setMat4("model", modelForPawn);

    drawCube(cubeVAO, lightingShader, alTogether * modelForPawn, r, g, b);

    identityMatrix = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::translate(identityMatrix, glm::vec3(cube_x + 0.065, cube_y + .68, cube_z + 0.725));
    scale = glm::scale(identityMatrix, glm::vec3(cube_height - 0.14, cube_w - 0.07, cube_b - 0.06));
    rotate = glm::mat4(1.0f);
    rotate = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    modelForPawn = alTogether * translate * rotate * scale;

    lightingShader.setMat4("model", modelForPawn);

    drawCube(cubeVAO, lightingShader, alTogether * modelForPawn, r, g, b);

    identityMatrix = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::translate(identityMatrix, glm::vec3(cube_x + .15, cube_y + .68, cube_z + 0.735));
    scale = glm::scale(identityMatrix, glm::vec3(cube_height - 0.14, cube_w - 0.07, cube_b - 0.06));
    rotate = glm::mat4(1.0f);
    rotate = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    modelForPawn = alTogether * translate * rotate * scale;

    lightingShader.setMat4("model", modelForPawn);

    drawCube(cubeVAO, lightingShader, alTogether * modelForPawn, r, g, b);

    identityMatrix = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);

    translate = glm::translate(identityMatrix, glm::vec3(cube_x + 0.070, cube_y + .65, cube_z + 0.725 + .15));
    scale = glm::scale(identityMatrix, glm::vec3(cube_height - 0.14, cube_w - 0.07, cube_b + 0.02));
    rotate = glm::mat4(1.0f);
    rotate = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    modelForPawn = alTogether * translate * rotate * scale;

    lightingShader.setMat4("model", modelForPawn);

    drawCube(cubeVAO, lightingShader, alTogether * modelForPawn, r, g, b);

    identityMatrix = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::translate(identityMatrix, glm::vec3(cube_x + 0.065, cube_y + .68, cube_z + 0.725 + .15));
    scale = glm::scale(identityMatrix, glm::vec3(cube_height - 0.14, cube_w - 0.07, cube_b - 0.06));
    rotate = glm::mat4(1.0f);
    rotate = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    modelForPawn = alTogether * translate * rotate * scale;

    lightingShader.setMat4("model", modelForPawn);

    drawCube(cubeVAO, lightingShader, alTogether * modelForPawn, r, g, b);

    identityMatrix = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::translate(identityMatrix, glm::vec3(cube_x + .15, cube_y + .68, cube_z + 0.735 + .15));
    scale = glm::scale(identityMatrix, glm::vec3(cube_height - 0.14, cube_w - 0.07, cube_b - 0.06));
    rotate = glm::mat4(1.0f);
    rotate = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    modelForPawn = alTogether * translate * rotate * scale;

    lightingShader.setMat4("model", modelForPawn);

    drawCube(cubeVAO, lightingShader, alTogether * modelForPawn, r, g, b);
}
    void rook2(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether, float cube_x, float cube_y, float cube_z,
    float cube_height, float cube_w, float cube_b, float r, float g, float b) {

    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translate, scale, modelForPawn;
    glm::mat4 rotate;
    rotate = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
    translate = glm::translate(identityMatrix, glm::vec3(cube_x + 0.05, cube_y + 0.40, cube_z + 0.75));
    scale = glm::scale(identityMatrix, glm::vec3(cube_height, cube_w, cube_b));
    modelForPawn = alTogether * translate * scale;
    lightingShader.setMat4("model", modelForPawn);

    drawCube(cubeVAO, lightingShader, alTogether * modelForPawn, r, g, b);

    identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::translate(identityMatrix, glm::vec3(cube_x + 0.08, cube_y + 0.5, cube_z + 0.75));
    scale = glm::scale(identityMatrix, glm::vec3(cube_height - 0.055, cube_w + 0.025, cube_b));
    modelForPawn = alTogether * translate * scale;

    lightingShader.setMat4("model", modelForPawn);

    drawCube(cubeVAO, lightingShader, alTogether * modelForPawn, r, g, b);

    identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::translate(identityMatrix, glm::vec3(cube_x + 0.065, cube_y + 0.6, cube_z + 0.725));
    scale = glm::scale(identityMatrix, glm::vec3(cube_height - 0.025, cube_w - 0.05, cube_b + 0.05));
    modelForPawn = alTogether * translate * scale;

    lightingShader.setMat4("model", modelForPawn);

    drawCube(cubeVAO, lightingShader, alTogether * modelForPawn, r, g, b);
    identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::translate(identityMatrix, glm::vec3(cube_x + 0.065, cube_y + 0.65, cube_z + 0.725));
    scale = glm::scale(identityMatrix, glm::vec3(cube_height - 0.14, cube_w - 0.07, cube_b + 0.05));
    modelForPawn = alTogether * translate * scale;

    lightingShader.setMat4("model", modelForPawn);

    drawCube(cubeVAO, lightingShader, alTogether * modelForPawn, r, g, b);

    identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::translate(identityMatrix, glm::vec3(cube_x + 0.065, cube_y + 0.68, cube_z + 0.725));
    scale = glm::scale(identityMatrix, glm::vec3(cube_height - 0.14, cube_w - 0.07, cube_b - 0.06));
    modelForPawn = alTogether * translate * scale;

    lightingShader.setMat4("model", modelForPawn);

    drawCube(cubeVAO, lightingShader, alTogether * modelForPawn, r, g, b);

    identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::translate(identityMatrix, glm::vec3(cube_x + 0.065, cube_y + 0.68, cube_z + 0.86 - 0.025));
    scale = glm::scale(identityMatrix, glm::vec3(cube_height - 0.14, cube_w - 0.07, cube_b - 0.06));
    modelForPawn = alTogether * translate * scale;

    lightingShader.setMat4("model", modelForPawn);

    drawCube(cubeVAO, lightingShader, alTogether * modelForPawn, r, g, b);


    identityMatrix = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::translate(identityMatrix, glm::vec3(cube_x + 0.065 + .115, cube_y + 0.65, cube_z + 0.725));
    scale = glm::scale(identityMatrix, glm::vec3(cube_height - 0.14, cube_w - 0.07, cube_b + 0.05));
    modelForPawn = alTogether * translate * scale;

    lightingShader.setMat4("model", modelForPawn);

    drawCube(cubeVAO, lightingShader, alTogether * modelForPawn, r, g, b);

    identityMatrix = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::translate(identityMatrix, glm::vec3(cube_x + 0.065 + .115, cube_y + 0.68, cube_z + 0.725));
    scale = glm::scale(identityMatrix, glm::vec3(cube_height - 0.14, cube_w - 0.07, cube_b - 0.06));
    modelForPawn = alTogether * translate * scale;

    lightingShader.setMat4("model", modelForPawn);

    drawCube(cubeVAO, lightingShader, alTogether * modelForPawn, r, g, b);

    identityMatrix = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::translate(identityMatrix, glm::vec3(cube_x + 0.065 + .115, cube_y + 0.68, cube_z + 0.86 - 0.025));
    scale = glm::scale(identityMatrix, glm::vec3(cube_height - 0.14, cube_w - 0.07, cube_b - 0.06));
    modelForPawn = alTogether * translate * scale;

    lightingShader.setMat4("model", modelForPawn);

    drawCube(cubeVAO, lightingShader, alTogether * modelForPawn, r, g, b);

    identityMatrix = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);

    translate = glm::translate(identityMatrix, glm::vec3(cube_x + 0.070, cube_y + .65, cube_z + 0.725));
    scale = glm::scale(identityMatrix, glm::vec3(cube_height - 0.14, cube_w - 0.07, cube_b + 0.02));
    rotate = glm::mat4(1.0f);
    rotate = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    modelForPawn = alTogether * translate * rotate * scale;

    lightingShader.setMat4("model", modelForPawn);

    drawCube(cubeVAO, lightingShader, alTogether * modelForPawn, r, g, b);

    identityMatrix = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::translate(identityMatrix, glm::vec3(cube_x + 0.065, cube_y + .68, cube_z + 0.725));
    scale = glm::scale(identityMatrix, glm::vec3(cube_height - 0.14, cube_w - 0.07, cube_b - 0.06));
    rotate = glm::mat4(1.0f);
    rotate = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    modelForPawn = alTogether * translate * rotate * scale;

    lightingShader.setMat4("model", modelForPawn);

    drawCube(cubeVAO, lightingShader, alTogether * modelForPawn, r, g, b);

    identityMatrix = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::translate(identityMatrix, glm::vec3(cube_x + .15, cube_y + .68, cube_z + 0.735));
    scale = glm::scale(identityMatrix, glm::vec3(cube_height - 0.14, cube_w - 0.07, cube_b - 0.06));
    rotate = glm::mat4(1.0f);
    rotate = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    modelForPawn = alTogether * translate * rotate * scale;

    lightingShader.setMat4("model", modelForPawn);

    drawCube(cubeVAO, lightingShader, alTogether * modelForPawn, r, g, b);

    identityMatrix = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);

    translate = glm::translate(identityMatrix, glm::vec3(cube_x + 0.070, cube_y + .65, cube_z + 0.725 + .15));
    scale = glm::scale(identityMatrix, glm::vec3(cube_height - 0.14, cube_w - 0.07, cube_b + 0.02));
    rotate = glm::mat4(1.0f);
    rotate = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    modelForPawn = alTogether * translate * rotate * scale;

    lightingShader.setMat4("model", modelForPawn);

    drawCube(cubeVAO, lightingShader, alTogether * modelForPawn, r, g, b);

    identityMatrix = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::translate(identityMatrix, glm::vec3(cube_x + 0.065, cube_y + .68, cube_z + 0.725 + .15));
    scale = glm::scale(identityMatrix, glm::vec3(cube_height - 0.14, cube_w - 0.07, cube_b - 0.06));
    rotate = glm::mat4(1.0f);
    rotate = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    modelForPawn = alTogether * translate * rotate * scale;

    lightingShader.setMat4("model", modelForPawn);

    drawCube(cubeVAO, lightingShader, alTogether * modelForPawn, r, g, b);

    identityMatrix = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::translate(identityMatrix, glm::vec3(cube_x + .15, cube_y + .68, cube_z + 0.735 + .15));
    scale = glm::scale(identityMatrix, glm::vec3(cube_height - 0.14, cube_w - 0.07, cube_b - 0.06));
    rotate = glm::mat4(1.0f);
    rotate = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    modelForPawn = alTogether * translate * rotate * scale;

    lightingShader.setMat4("model", modelForPawn);

    drawCube(cubeVAO, lightingShader, alTogether * modelForPawn, r, g, b);
}

void rook3(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether, float cube_x, float cube_y, float cube_z,
    float cube_height, float cube_w, float cube_b, float r, float g, float b) {

    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translate, scale, modelForPawn;
    glm::mat4 rotate;
    rotate = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
    translate = glm::translate(identityMatrix, glm::vec3(cube_x + 0.05, cube_y + 0.40, cube_z + 0.75));
    scale = glm::scale(identityMatrix, glm::vec3(cube_height, cube_w, cube_b));
    modelForPawn = alTogether * translate * scale;
    lightingShader.setMat4("model", modelForPawn);

    drawCube(cubeVAO, lightingShader, alTogether * modelForPawn, r, g, b);

    identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::translate(identityMatrix, glm::vec3(cube_x + 0.08, cube_y + 0.5, cube_z + 0.75));
    scale = glm::scale(identityMatrix, glm::vec3(cube_height - 0.055, cube_w + 0.025, cube_b));
    modelForPawn = alTogether * translate * scale;

    lightingShader.setMat4("model", modelForPawn);

    drawCube(cubeVAO, lightingShader, alTogether * modelForPawn, r, g, b);

    identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::translate(identityMatrix, glm::vec3(cube_x + 0.065, cube_y + 0.6, cube_z + 0.725));
    scale = glm::scale(identityMatrix, glm::vec3(cube_height - 0.025, cube_w - 0.05, cube_b + 0.05));
    modelForPawn = alTogether * translate * scale;

    lightingShader.setMat4("model", modelForPawn);

    drawCube(cubeVAO, lightingShader, alTogether * modelForPawn, r, g, b);
    identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::translate(identityMatrix, glm::vec3(cube_x + 0.065, cube_y + 0.65, cube_z + 0.725));
    scale = glm::scale(identityMatrix, glm::vec3(cube_height - 0.14, cube_w - 0.07, cube_b + 0.05));
    modelForPawn = alTogether * translate * scale;

    lightingShader.setMat4("model", modelForPawn);

    drawCube(cubeVAO, lightingShader, alTogether * modelForPawn, r, g, b);

    identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::translate(identityMatrix, glm::vec3(cube_x + 0.065, cube_y + 0.68, cube_z + 0.725));
    scale = glm::scale(identityMatrix, glm::vec3(cube_height - 0.14, cube_w - 0.07, cube_b - 0.06));
    modelForPawn = alTogether * translate * scale;

    lightingShader.setMat4("model", modelForPawn);

    drawCube(cubeVAO, lightingShader, alTogether * modelForPawn, r, g, b);

    identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::translate(identityMatrix, glm::vec3(cube_x + 0.065, cube_y + 0.68, cube_z + 0.86 - 0.025));
    scale = glm::scale(identityMatrix, glm::vec3(cube_height - 0.14, cube_w - 0.07, cube_b - 0.06));
    modelForPawn = alTogether * translate * scale;

    lightingShader.setMat4("model", modelForPawn);

    drawCube(cubeVAO, lightingShader, alTogether * modelForPawn, r, g, b);


    identityMatrix = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::translate(identityMatrix, glm::vec3(cube_x + 0.065 + .115, cube_y + 0.65, cube_z + 0.725));
    scale = glm::scale(identityMatrix, glm::vec3(cube_height - 0.14, cube_w - 0.07, cube_b + 0.05));
    modelForPawn = alTogether * translate * scale;

    lightingShader.setMat4("model", modelForPawn);

    drawCube(cubeVAO, lightingShader, alTogether * modelForPawn, r, g, b);

    identityMatrix = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::translate(identityMatrix, glm::vec3(cube_x + 0.065 + .115, cube_y + 0.68, cube_z + 0.725));
    scale = glm::scale(identityMatrix, glm::vec3(cube_height - 0.14, cube_w - 0.07, cube_b - 0.06));
    modelForPawn = alTogether * translate * scale;

    lightingShader.setMat4("model", modelForPawn);

    drawCube(cubeVAO, lightingShader, alTogether * modelForPawn, r, g, b);

    identityMatrix = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::translate(identityMatrix, glm::vec3(cube_x + 0.065 + .115, cube_y + 0.68, cube_z + 0.86 - 0.025));
    scale = glm::scale(identityMatrix, glm::vec3(cube_height - 0.14, cube_w - 0.07, cube_b - 0.06));
    modelForPawn = alTogether * translate * scale;

    lightingShader.setMat4("model", modelForPawn);

    drawCube(cubeVAO, lightingShader, alTogether * modelForPawn, r, g, b);

    identityMatrix = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);

    translate = glm::translate(identityMatrix, glm::vec3(cube_x + 0.070, cube_y + .65, cube_z + 0.725));
    scale = glm::scale(identityMatrix, glm::vec3(cube_height - 0.14, cube_w - 0.07, cube_b + 0.02));
    rotate = glm::mat4(1.0f);
    rotate = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    modelForPawn = alTogether * translate * rotate * scale;

    lightingShader.setMat4("model", modelForPawn);

    drawCube(cubeVAO, lightingShader, alTogether * modelForPawn, r, g, b);

    identityMatrix = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::translate(identityMatrix, glm::vec3(cube_x + 0.065, cube_y + .68, cube_z + 0.725));
    scale = glm::scale(identityMatrix, glm::vec3(cube_height - 0.14, cube_w - 0.07, cube_b - 0.06));
    rotate = glm::mat4(1.0f);
    rotate = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    modelForPawn = alTogether * translate * rotate * scale;

    lightingShader.setMat4("model", modelForPawn);

    drawCube(cubeVAO, lightingShader, alTogether * modelForPawn, r, g, b);

    identityMatrix = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::translate(identityMatrix, glm::vec3(cube_x + .15, cube_y + .68, cube_z + 0.735));
    scale = glm::scale(identityMatrix, glm::vec3(cube_height - 0.14, cube_w - 0.07, cube_b - 0.06));
    rotate = glm::mat4(1.0f);
    rotate = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    modelForPawn = alTogether * translate * rotate * scale;

    lightingShader.setMat4("model", modelForPawn);

    drawCube(cubeVAO, lightingShader, alTogether * modelForPawn, r, g, b);

    identityMatrix = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);

    translate = glm::translate(identityMatrix, glm::vec3(cube_x + 0.070, cube_y + .65, cube_z + 0.725 + .15));
    scale = glm::scale(identityMatrix, glm::vec3(cube_height - 0.14, cube_w - 0.07, cube_b + 0.02));
    rotate = glm::mat4(1.0f);
    rotate = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    modelForPawn = alTogether * translate * rotate * scale;

    lightingShader.setMat4("model", modelForPawn);

    drawCube(cubeVAO, lightingShader, alTogether * modelForPawn, r, g, b);

    identityMatrix = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::translate(identityMatrix, glm::vec3(cube_x + 0.065, cube_y + .68, cube_z + 0.725 + .15));
    scale = glm::scale(identityMatrix, glm::vec3(cube_height - 0.14, cube_w - 0.07, cube_b - 0.06));
    rotate = glm::mat4(1.0f);
    rotate = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    modelForPawn = alTogether * translate * rotate * scale;

    lightingShader.setMat4("model", modelForPawn);

    drawCube(cubeVAO, lightingShader, alTogether * modelForPawn, r, g, b);

    identityMatrix = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::translate(identityMatrix, glm::vec3(cube_x + .15, cube_y + .68, cube_z + 0.735 + .15));
    scale = glm::scale(identityMatrix, glm::vec3(cube_height - 0.14, cube_w - 0.07, cube_b - 0.06));
    rotate = glm::mat4(1.0f);
    rotate = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    modelForPawn = alTogether * translate * rotate * scale;

    lightingShader.setMat4("model", modelForPawn);

    drawCube(cubeVAO, lightingShader, alTogether * modelForPawn, r, g, b);
}
void rook4(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether, float cube_x, float cube_y, float cube_z,
    float cube_height, float cube_w, float cube_b, float r, float g, float b) {

    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translate, scale, modelForPawn;
    glm::mat4 rotate;
    rotate = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
    translate = glm::translate(identityMatrix, glm::vec3(cube_x + 0.05, cube_y + 0.40, cube_z + 0.75));
    scale = glm::scale(identityMatrix, glm::vec3(cube_height, cube_w, cube_b));
    modelForPawn = alTogether * translate * scale;
    lightingShader.setMat4("model", modelForPawn);

    drawCube(cubeVAO, lightingShader, alTogether * modelForPawn, r, g, b);

    identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::translate(identityMatrix, glm::vec3(cube_x + 0.08, cube_y + 0.5, cube_z + 0.75));
    scale = glm::scale(identityMatrix, glm::vec3(cube_height - 0.055, cube_w + 0.025, cube_b));
    modelForPawn = alTogether * translate * scale;

    lightingShader.setMat4("model", modelForPawn);

    drawCube(cubeVAO, lightingShader, alTogether * modelForPawn, r, g, b);

    identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::translate(identityMatrix, glm::vec3(cube_x + 0.065, cube_y + 0.6, cube_z + 0.725));
    scale = glm::scale(identityMatrix, glm::vec3(cube_height - 0.025, cube_w - 0.05, cube_b + 0.05));
    modelForPawn = alTogether * translate * scale;

    lightingShader.setMat4("model", modelForPawn);

    drawCube(cubeVAO, lightingShader, alTogether * modelForPawn, r, g, b);
    identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::translate(identityMatrix, glm::vec3(cube_x + 0.065, cube_y + 0.65, cube_z + 0.725));
    scale = glm::scale(identityMatrix, glm::vec3(cube_height - 0.14, cube_w - 0.07, cube_b + 0.05));
    modelForPawn = alTogether * translate * scale;

    lightingShader.setMat4("model", modelForPawn);

    drawCube(cubeVAO, lightingShader, alTogether * modelForPawn, r, g, b);

    identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::translate(identityMatrix, glm::vec3(cube_x + 0.065, cube_y + 0.68, cube_z + 0.725));
    scale = glm::scale(identityMatrix, glm::vec3(cube_height - 0.14, cube_w - 0.07, cube_b - 0.06));
    modelForPawn = alTogether * translate * scale;

    lightingShader.setMat4("model", modelForPawn);

    drawCube(cubeVAO, lightingShader, alTogether * modelForPawn, r, g, b);

    identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::translate(identityMatrix, glm::vec3(cube_x + 0.065, cube_y + 0.68, cube_z + 0.86 - 0.025));
    scale = glm::scale(identityMatrix, glm::vec3(cube_height - 0.14, cube_w - 0.07, cube_b - 0.06));
    modelForPawn = alTogether * translate * scale;

    lightingShader.setMat4("model", modelForPawn);

    drawCube(cubeVAO, lightingShader, alTogether * modelForPawn, r, g, b);


    identityMatrix = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::translate(identityMatrix, glm::vec3(cube_x + 0.065 + .115, cube_y + 0.65, cube_z + 0.725));
    scale = glm::scale(identityMatrix, glm::vec3(cube_height - 0.14, cube_w - 0.07, cube_b + 0.05));
    modelForPawn = alTogether * translate * scale;

    lightingShader.setMat4("model", modelForPawn);

    drawCube(cubeVAO, lightingShader, alTogether * modelForPawn, r, g, b);

    identityMatrix = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::translate(identityMatrix, glm::vec3(cube_x + 0.065 + .115, cube_y + 0.68, cube_z + 0.725));
    scale = glm::scale(identityMatrix, glm::vec3(cube_height - 0.14, cube_w - 0.07, cube_b - 0.06));
    modelForPawn = alTogether * translate * scale;

    lightingShader.setMat4("model", modelForPawn);

    drawCube(cubeVAO, lightingShader, alTogether * modelForPawn, r, g, b);

    identityMatrix = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::translate(identityMatrix, glm::vec3(cube_x + 0.065 + .115, cube_y + 0.68, cube_z + 0.86 - 0.025));
    scale = glm::scale(identityMatrix, glm::vec3(cube_height - 0.14, cube_w - 0.07, cube_b - 0.06));
    modelForPawn = alTogether * translate * scale;

    lightingShader.setMat4("model", modelForPawn);

    drawCube(cubeVAO, lightingShader, alTogether * modelForPawn, r, g, b);

    identityMatrix = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);

    translate = glm::translate(identityMatrix, glm::vec3(cube_x + 0.070, cube_y + .65, cube_z + 0.725));
    scale = glm::scale(identityMatrix, glm::vec3(cube_height - 0.14, cube_w - 0.07, cube_b + 0.02));
    rotate = glm::mat4(1.0f);
    rotate = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    modelForPawn = alTogether * translate * rotate * scale;

    lightingShader.setMat4("model", modelForPawn);

    drawCube(cubeVAO, lightingShader, alTogether * modelForPawn, r, g, b);

    identityMatrix = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::translate(identityMatrix, glm::vec3(cube_x + 0.065, cube_y + .68, cube_z + 0.725));
    scale = glm::scale(identityMatrix, glm::vec3(cube_height - 0.14, cube_w - 0.07, cube_b - 0.06));
    rotate = glm::mat4(1.0f);
    rotate = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    modelForPawn = alTogether * translate * rotate * scale;

    lightingShader.setMat4("model", modelForPawn);

    drawCube(cubeVAO, lightingShader, alTogether * modelForPawn, r, g, b);

    identityMatrix = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::translate(identityMatrix, glm::vec3(cube_x + .15, cube_y + .68, cube_z + 0.735));
    scale = glm::scale(identityMatrix, glm::vec3(cube_height - 0.14, cube_w - 0.07, cube_b - 0.06));
    rotate = glm::mat4(1.0f);
    rotate = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    modelForPawn = alTogether * translate * rotate * scale;

    lightingShader.setMat4("model", modelForPawn);

    drawCube(cubeVAO, lightingShader, alTogether * modelForPawn, r, g, b);

    identityMatrix = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);

    translate = glm::translate(identityMatrix, glm::vec3(cube_x + 0.070, cube_y + .65, cube_z + 0.725 + .15));
    scale = glm::scale(identityMatrix, glm::vec3(cube_height - 0.14, cube_w - 0.07, cube_b + 0.02));
    rotate = glm::mat4(1.0f);
    rotate = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    modelForPawn = alTogether * translate * rotate * scale;

    lightingShader.setMat4("model", modelForPawn);

    drawCube(cubeVAO, lightingShader, alTogether * modelForPawn, r, g, b);

    identityMatrix = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::translate(identityMatrix, glm::vec3(cube_x + 0.065, cube_y + .68, cube_z + 0.725 + .15));
    scale = glm::scale(identityMatrix, glm::vec3(cube_height - 0.14, cube_w - 0.07, cube_b - 0.06));
    rotate = glm::mat4(1.0f);
    rotate = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    modelForPawn = alTogether * translate * rotate * scale;

    lightingShader.setMat4("model", modelForPawn);

    drawCube(cubeVAO, lightingShader, alTogether * modelForPawn, r, g, b);

    identityMatrix = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::translate(identityMatrix, glm::vec3(cube_x + .15, cube_y + .68, cube_z + 0.735 + .15));
    scale = glm::scale(identityMatrix, glm::vec3(cube_height - 0.14, cube_w - 0.07, cube_b - 0.06));
    rotate = glm::mat4(1.0f);
    rotate = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    modelForPawn = alTogether * translate * rotate * scale;

    lightingShader.setMat4("model", modelForPawn);

    drawCube(cubeVAO, lightingShader, alTogether * modelForPawn, r, g, b);
}

void queen2(unsigned int& bezierVAO, unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether, float x, float y, float z, float h, float w,
    float b, float r, float g, float bl) {

    glm::mat4 modelForQueen = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    glm::mat4 rotate = glm::mat4(1.0f);
    translate = glm::translate(modelForQueen, glm::vec3(x, y, z));
    scale = glm::scale(modelForQueen, glm::vec3(h, w, b));
    modelForQueen = alTogether * translate * scale;
    drawCurve(bezierVAO, lightingShader, modelForQueen, r, g, bl);

    modelForQueen = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    rotate = glm::mat4(1.0f);
    modelForQueen = alTogether * translate * scale;
    drawSphere(lightingShader, alTogether * modelForQueen, x, 0.60, z, 0.09f, 0.03f, 0.09f, r, g, bl);

    modelForQueen = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    rotate = glm::mat4(1.0f);
    modelForQueen = alTogether * translate * scale;
    drawSphere(lightingShader, alTogether * modelForQueen, x, 0.505, z, 0.105f, 0.045f, 0.105f, r, g, bl);

    modelForQueen = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    rotate = glm::mat4(1.0f);
    modelForQueen = alTogether * translate * scale;
    drawSphere(lightingShader, alTogether * modelForQueen, x, 0.325, z, 0.15f, 0.075f, 0.15f, r, g, bl);

    modelForQueen = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    rotate = glm::mat4(1.0f);
    modelForQueen = alTogether * translate * scale;
    drawSphere(lightingShader, alTogether * modelForQueen, x, 0.625, z, 0.04f, 0.04f, 0.04f, r, g, bl);
}



void king2(unsigned int& bezierVAO, unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether, float x, float y, float z, float h, float w,
    float b, float r, float g, float bl, float cube_x, float cube_y, float cube_z) {

    glm::mat4 modelForKing = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    glm::mat4 rotate = glm::mat4(1.0f);
    translate = glm::translate(modelForKing, glm::vec3(x, y, z));
    scale = glm::scale(modelForKing, glm::vec3(h, w, b));
    modelForKing = alTogether * translate * scale;
    drawCurve(bezierVAO, lightingShader, modelForKing, r, g, bl);

    modelForKing = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    rotate = glm::mat4(1.0f);
    modelForKing = alTogether * translate * scale;
    drawSphere(lightingShader, alTogether * modelForKing, x, 0.60, z, 0.09f, 0.03f, 0.09f, r, g, bl);

    modelForKing = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    rotate = glm::mat4(1.0f);
    modelForKing = alTogether * translate * scale;
    drawSphere(lightingShader, alTogether * modelForKing, x, 0.505, z, 0.105f, 0.045f, 0.105f, r, g, bl);

    modelForKing = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    rotate = glm::mat4(1.0f);
    modelForKing = alTogether * translate * scale;
    drawSphere(lightingShader, alTogether * modelForKing, x, 0.325, z, 0.15f, 0.075f, 0.15f, r, g, bl);

    modelForKing = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    rotate = glm::mat4(1.0f);
    translate = glm::translate(modelForKing, glm::vec3(cube_x - 0.01, cube_y + 0.375, cube_z ));
    scale = glm::scale(modelForKing, glm::vec3(0.02f, 0.06f, 0.02f));
    modelForKing = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, alTogether * modelForKing, r, g, bl);

    modelForKing = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    rotate = glm::mat4(1.0f);
    translate = glm::translate(modelForKing, glm::vec3(cube_x - 0.0325, cube_y + 0.395, cube_z ));
    scale = glm::scale(modelForKing, glm::vec3(0.06f, 0.02f, 0.02f));
    modelForKing = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, alTogether * modelForKing, r, g, bl);

}
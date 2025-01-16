#include <gl/glut.h>

float rotationAngle = 0.0;
bool hidden = false;
bool isRotating = true;
float translateX = 0.0, translateY = 0.0, translateZ = 0.0;
float scaleX = 1.0, scaleY = 1.0, scaleZ = 1.0;
float rotateX = 0.0, rotateY = 1.0, rotateZ = 0.0;
float roomScaleX = 8.0, roomScaleY = 8.0, roomScaleZ = 8.0;
float pintuScaleX = 1.0, pintuScaleY = 2.0, pintuScaleZ = 0.1;
float lightPosX = 0.0f, lightPosY = 8.0f, lightPosZ = 0.0f;

//Prototype
void Transformasi();
void drawCartecius();
void hiddenCarte();
void Meja();
void Kursi();
void Pintu();
void GagangPintu();
void Ruangan();
void Furniture();
void mySpecialKeys(int key, int x, int y);
void setupLighting();
void window();
void init3DProjection();
void myKeyboard(unsigned char key, int x, int y);
void Laptop();

//Rifky Dzulfikri
void Transformasi() {
    glTranslatef(translateX, translateY, translateZ);
    glScalef(scaleX, scaleY, scaleZ);
    glRotatef(rotationAngle, rotateX, rotateY, rotateZ);
}

void drawCartecius() {
    glPushMatrix();
    glTranslatef(0.0f, 0.6f, 0.0f);  // Posisi sistem koordinat di atas meja

    glColor3f(1.0, 1.0, 1.0);  // Warna garis Cartesius
    glBegin(GL_LINES);
    glVertex3f(-50.0, 0.0, 0.0);
    glVertex3f(50.0, 0.0, 0.0);
    glVertex3f(0.0, -50.0, 0.0);
    glVertex3f(0.0, 50.0, 0.0);
    glVertex3f(0.0, 0.0, -50.0);
    glVertex3f(0.0, 0.0, 50.0);
    glEnd();
    
    glPopMatrix();
}

void hiddenCarte() {
    if (hidden) {
        drawCartecius();
    }
}

// Fungsi untuk menggambar meja
void Meja() {
    // Permukaan meja
    glPushMatrix();
    glColor3f(0.6f, 0.3f, 0.1f);
    glTranslatef(0.0f, 0.5f, 0.0f);
  	glScalef(2.0f, 0.1f, 1.0f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Kaki-kaki meja
    float legHeight = 1.0f;
    glColor3f(0.4f, 0.2f, 0.1f);
    for (float x = -0.9f; x <= 0.9f; x += 1.8f) {
        for (float z = -0.4f; z <= 0.4f; z += 0.8f) {
            glPushMatrix();
            glTranslatef(x, legHeight / 1.0f - 1.0f, z);
            glScalef(0.1f, legHeight, 0.1f);
            glutSolidCube(1.0f);
            glPopMatrix();
        }
    }
}

// Fungsi untuk menggambar kursi
void Kursi() {
    // Dudukan kursi
    glPushMatrix();
    glColor3f(0.6f, 0.3f, 0.1f);
    glTranslatef(0.0f, 0.5f, 0.0f);
    glScalef(1.0f, 0.1f, 1.0f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Kaki-kaki kursi
    float legHeight = 0.5f;
    glColor3f(0.4f, 0.2f, 0.1f);
    for (float x = -0.4f; x <= 0.4f; x += 0.8f) {
        for (float z = -0.4f; z <= 0.4f; z += 0.8f) {
            glPushMatrix();
            glTranslatef(x, legHeight / 2.0f, z);
            glScalef(0.1f, legHeight, 0.1f);
            glutSolidCube(1.0f);
            glPopMatrix();
        }
    }

    // Sandaran kursi
    glPushMatrix();
    glColor3f(0.6f, 0.3f, 0.1f);
    glTranslatef(0.0f, 0.9f, -0.4f);
    glScalef(1.0f, 0.8f, 0.1f);
    glutSolidCube(1.0f);
    glPopMatrix();
}

//Aisha Kamil
void Pintu() {
  glPushMatrix();
  glColor3f(0.5f, 0.5f, 0.5f);
  glTranslatef(2.0f, 1.0f, 5.5f);
  glScalef(pintuScaleX, pintuScaleY, pintuScaleZ);
  glutSolidCube(1.0f);
  glPopMatrix();
}

void GagangPintu() {
	glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f);
	glTranslatef(2.4f, 1.0f, 5.5f);
	glutSolidSphere(0.1, 10, 10);
	glPopMatrix();
}

void Ruangan() {
    glPushMatrix();
    glColor3ub(177, 240, 247);
    glScalef(roomScaleX, roomScaleY, roomScaleZ);
    glutSolidCube(1.0f);
    
    glColor3f(1.0f, 1.0f, 1.0f);
    glutWireCube(0.99f);
    glPopMatrix();
}

void Furniture() {
    // Meja
    glPushMatrix();
    glTranslatef(0.0f, -3.5f, 0.0f);
    Meja();
    glPopMatrix();

    // Kursi 1
    glPushMatrix();
    glTranslatef(0.0f, -4.05f, 1.5f);
    glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
    Kursi();
    glPopMatrix();

    // Kursi 2
    glPushMatrix();
    glTranslatef(0.0f, -4.05f, -1.5f);
    Kursi();
    Pintu();
    GagangPintu();
    glPopMatrix();
    
    glPushMatrix();
    Laptop();
    glPopMatrix();
}

void mySpecialKeys(int key, int x, int y)
{
switch (key)
{
case GLUT_KEY_LEFT:
    gluLookAt(-0.3, 0.0, 0.0, // Posisi kamera
                      0.0, 0.0, 0.0,  // Titik yang dituju kamera
                      0.0, 1.0, 0.0); // Vektor up
    break;
case GLUT_KEY_RIGHT:
    gluLookAt(0.3, 0.0, 0.0,  // Posisi kamera
                      0.0, 0.0, 0.0,  // Titik yang dituju kamera
                      0.0, 1.0, 0.0); // Vektor up
    break;
}
glutPostRedisplay();
}

//eva carlia
void setupLighting() {
    // Posisi cahaya yang dapat diubah (digunakan dalam fungsi ini)
    GLfloat lightPos[] = { lightPosX, lightPosY, lightPosZ, 1.0f };
    GLfloat lightAmbient[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    GLfloat lightDiffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    GLfloat lightSpecular[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
}  

void window() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
	glPushMatrix();
    Transformasi();
    hiddenCarte();
    Ruangan();
    Furniture();
    
	glPopMatrix();
    glutSwapBuffers();
    glutPostRedisplay();
    if (isRotating)
        rotationAngle += 0.02;
}

void init3DProjection() {
    glutCreateWindow("UAS");
    glutDisplayFunc(window);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(35.0, 1.0, 7.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(1.0, -1.0, 10.0,
        0.0, -2.0, 0.0,
        0.0, 10.0, 0.0);

    setupLighting();
}

void myKeyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 27:
            exit(0);
            break;
    case 'c':
        hidden =! hidden;
        break;
    case 'r':
        isRotating = !isRotating;
        break;
    case 'b':
        if (roomScaleX < 8.0, roomScaleY < 8.0, roomScaleZ < 8.0 ) {
        roomScaleX += 1.0;
        roomScaleY += 1.0;
        roomScaleZ += 1.0;
    	}
        break;
    case 'k':
    	 if (roomScaleX > 0.0, roomScaleY > 0.0, roomScaleZ > 0.0 ) {
        roomScaleX -= 1.0;
        roomScaleY -= 1.0;
        roomScaleZ -= 1.0;
    	}
        break;
    case 'a':  // Geser cahaya ke kiri
        lightPosX -= 0.5f;
        break;
    case 'd':  // Geser cahaya ke kanan
        lightPosX += 0.5f;
        break;
    case 'w':  // Geser cahaya ke atas
        lightPosY += 0.5f;
        break;
    case 's':  // Geser cahaya ke bawah
        lightPosY -= 0.5f;
        break;
    }
    setupLighting();
    glutPostRedisplay();
}

void Laptop() {
    glPushMatrix();
    glColor3f(0.2f, 0.2f, 0.3f); // Warna bodi laptop
    glTranslatef(0.0f, -2.92f, 0.3f); // Posisi laptop di atas meja
    glScalef(0.7f, 0.06f, 0.4f);   // Skala bodi laptop
    glutSolidCube(1.0f);           // Gambar bodi laptop
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.2f, 0.2f, 0.3f); // Warna layar laptop
    glTranslatef(0.0f, -2.69f, 0.1f); // Posisi layar laptop
    glScalef(0.7f, 0.57f, 0.06f);   // Skala layar laptop
    glutSolidCube(1.0f);           // Gambar layar laptop
    glPopMatrix();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(700, 600);
    glutInitWindowPosition(200, 0);
    init3DProjection();
    glutKeyboardFunc(myKeyboard);
    glutSpecialFunc(mySpecialKeys);
    glutMainLoop();
    return 0;
}

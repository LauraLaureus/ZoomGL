
#include "main.h"

//main
int main(int argc, char *argv[]){
    
    glutInit(&argc, argv);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(WINDOW_ANCHO, WINDOW_ALTO);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    
    glutCreateWindow("OpenGL Practica ");
    InitGL();
    glutDisplayFunc(Display); // registra la funcion de rendering
    glutReshapeFunc(ReshapeSize);
    glutMotionFunc(PosicionRaton);
    glutSpecialFunc(RuedaRaton);
    
    glutMainLoop(); // bucle principal
    
    return 0;
}



void setViewport(){
    int ancho = glutGet(GLUT_WINDOW_WIDTH);
    int alto = glutGet(GLUT_WINDOW_HEIGHT);
    glViewport(0, 0, ancho, alto); // utiliza la totalidad de la ventana
}

void setProjection(){
    int ancho = glutGet(GLUT_WINDOW_WIDTH);
    int alto = glutGet(GLUT_WINDOW_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(gl_fovy, (float)ancho / (float)alto, gl_cerca, gl_lejos);
}

void setModelView(){
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void InitGL(){
    
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    // para cambiar el criterio de lo que se ve.
    // LESS es el de defecto: se ve lo que tiene menor profundidad
    glDepthFunc(GL_LESS);
    // TO DO
    
    setViewport();
    setProjection();
}

// cambio de dimensiones de la ventana, manteniendo la dimension de los objetos
void ReshapeSize(int ancho, int alto){
    
    setViewport();
    setProjection();
    glutPostRedisplay();
}

void PosicionRaton(int x, int y){
    
    int ancho = glutGet(GLUT_WINDOW_WIDTH);
    int alto = glutGet(GLUT_WINDOW_HEIGHT);
    
    theta = M_PI*(double)y / (double)alto;
    phi = - M_PI + 2*M_PI * (double)x / (double)ancho;
    glutPostRedisplay();
}

void RuedaRaton(int key, int x, int y){
    float sentido;
    if(key == GLUT_KEY_UP) sentido = 1;
    if(key == GLUT_KEY_DOWN) sentido = -1;
    if(key == GLUT_KEY_UP || key == GLUT_KEY_DOWN ){
        gl_fovy -= gl_fovy_paso*(float)sentido;
        if (gl_fovy < gl_fovy_min) gl_fovy = gl_fovy_min;
        if (gl_fovy > gl_fovy_max) gl_fovy = gl_fovy_max;
        setProjection();
    }
    glutPostRedisplay();
}





// función de gestion de ventana
void Display(){
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // borra todo lo existente en el framebuffer
    setModelView();
    
    // poicionamos el centro de coordenadas
    glTranslatef(0.0f, 0.0f, -gl_center);
    
    // el eje cenital es el Y
    float x = (float)(radio*sin(theta)*sin(phi));
    float y = (float)(radio*cos(theta));
    float z = (float)(radio*sin(theta)*cos(phi));
    gluLookAt(x,y,z,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f); // mira al (0,0,0)
    
    // TO DO
    glutWireTeapot(1.0f);
    
    
    
    glFlush(); // actualiza el framebuffer
    glutSwapBuffers(); // en caso de animacion
}


// PlantillaOpenGL.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"

#include <stdio.h>
#include <stdlib.h>

#define GLEW_STATIC

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <iostream>

#include "Shader.h"
#include "Vertice.h"
#include "Nave.h"

#include "Modelo.h"
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"


using namespace std;

//Declaramos apuntador de ventana
GLFWwindow *window;

Nave *nave;


Shader *shader;
GLuint posicionID;
GLuint colorID;
GLuint transformacionesID;



void dibujar() {
	
	nave->dibujar(GL_TRIANGLES);

}

void actualizar() {

	//---
	nave->tiempoActual = glfwGetTime();
	nave->tiempoDiferencial = nave->tiempoActual - nave->tiempoAnterior;
	//----
	nave->tiempoAnterior = nave->tiempoActual;

	nave->estadoDerecha = glfwGetKey(window, GLFW_KEY_RIGHT);
	nave->estadoIzquierda = glfwGetKey(window, GLFW_KEY_LEFT);
	nave->estadoArriba = glfwGetKey(window, GLFW_KEY_UP);
	nave->estadoAbajo = glfwGetKey(window, GLFW_KEY_DOWN);

	if (nave->estadoDerecha == GLFW_PRESS) {

		nave->rotar(Nave::Direccion::Derecha);
		nave->angulo -= nave->velocidadAngular * nave->tiempoDiferencial;

		if (nave->angulo < 0.0f) {
			nave->angulo += 360.0f;
		}

	}

	if (nave->estadoIzquierda == GLFW_PRESS) {

		nave->rotar(Nave::Direccion::Izquierda);
		nave->angulo += nave->velocidadAngular * nave->tiempoDiferencial;

		if (nave->angulo > 360.0f) {
			nave->angulo -= 360.0f;
		}

	}

	if (nave->estadoArriba == GLFW_PRESS) {

		nave->avanzar(Nave::Direccion::Arriba);
		nave->anguloTrayectoria = nave->angulo;

		if (nave->velocidadActual <= nave->velocidad) {
			nave->velocidadActual += nave->aceleracion * nave->tiempoDiferencial;
		}

	}
	else {
		if (nave->velocidadActual >= 0.0f) {
			nave->velocidadActual -= nave->desaceleracion * nave->tiempoDiferencial;

			if (nave->velocidadActual < 0.0f) {
				nave->velocidadActual = 0.0f;
			}

		}

	}

	
	
}


int main()
{
	
	
	//Si no se pudo iniciar glfw
	//terminamos ejcución
	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}
	//Si se pudo iniciar GLFW
	//entonces inicializamos la ventana
	window = glfwCreateWindow(1024, 768, "Ventana", 
			NULL, NULL);
	//Si no podemos iniciar la ventana
	//Entonces terminamos ejecucion
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	//Establecemos el contexto
	glfwMakeContextCurrent(window);

	//Una vez establecido  el contexto
	//Activamos funciones modernas
	glewExperimental = true;
	GLenum errorGlew = glewInit();

	if (errorGlew != GLEW_OK) {
		cout << glewGetErrorString(errorGlew);
	}

	const GLubyte *versionGL = glGetString(GL_VERSION);
	cout << "Version OpenGL: " << versionGL;



	//---
	

	//---------------------------------------------------------------------....................................................................................

	//AQUI INICIALIZAMOS METODOS/PROCEDIMIENTO
	

	
	//--------------------


	const char *rutaVertex = "VertexShader.shader";
	const char *rutaFragment = "FragmentShader.shader";

	shader = new Shader(rutaVertex, rutaFragment);
	
	//Mapeo de atributos
	posicionID = glGetAttribLocation(shader->getID(), "posicion");
	colorID = glGetAttribLocation(shader->getID(), "color");

	transformacionesID = glGetUniformLocation(shader->getID(), "transformaciones");
	

	//-------------AQUI MANDAMOS LLAMAR LOS SHADERS Y VERTEX ARRAY DE LOS OBJETOS------------------------

	nave = new Nave();
	nave->tiempoAnterior = glfwGetTime();
	nave->shader = shader;
	nave->inicializarVertexArray(posicionID, colorID, transformacionesID);
	

	/*
	//Establecer shader al modelo
	"loquedibuje"->shader = shader;
	//Inicializar el vertex array
	"loquedibuje"->inicializarVertexArray(posicionID, colorID, transformacionesID);
	*/



	//----------------------------------------------------------------------....................................................................................



	//Desenlazar el shader
	shader->desenlazar();

	
	//Ciclo de dibujo (Draw loop)
	while (!glfwWindowShouldClose(window)) {

		//Esablecer region de dibujo
		glViewport(0, 0, 1024, 768);

		//Establece el color de borrado
		glClearColor(1.0f, 0.2f, 0.5f, 1.0f);

		//Borramos
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Rutina de dibujo
		dibujar();
		actualizar();

		//Cambiar los buffers
		glfwSwapBuffers(window);

		//Reconocer si hay entradas
		glfwPollEvents();

	}

	glfwDestroyWindow(window);
	glfwTerminate();

    return 0;

}


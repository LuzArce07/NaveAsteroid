#pragma once

#include <stdio.h>
#include <stdlib.h>
#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "Shader.h"
#include "Vertice.h"

#include "Modelo.h"

#include "glm/gtx/transform.hpp"
#include "glm/glm.hpp"


class Nave : public Modelo {

public:

	Nave();
	
	enum Direccion {Izquierda, Derecha, Arriba};

	vec3 coordenadas;

	float xTriangulo;
	float yTriangulo;

	float angulo; //Angulo triangulo

	float anguloTrayectoria;
	
	float velocidadAngular = 0.1f;
	float velocidad = 0.0001f;
	

	float velocidadActual;
	float aceleracion;
	float desaceleracion;

	float tiempoAnterior;
	float tiempoActual;
	float tiempoDiferencial;

	int estadoDerecha;
	int estadoIzquierda;
	int estadoArriba;
	int estadoAbajo;

	void rotar(Direccion direccion);

	void avanzar(Direccion direccion);

	void actualizarMatrizTransformacion();


};

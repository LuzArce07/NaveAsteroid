#include "stdafx.h"
#include "Nave.h"



Nave::Nave() {

	xTriangulo = 0.0f;
	yTriangulo = 0.0f;

	angulo = 0.0f;
	
	anguloTrayectoria = 0.0f;
	velocidadAngular;

	velocidad;

	velocidadActual = 0.7f;
	aceleracion = 0.3f;
	desaceleracion = 0.2f;

	tiempoAnterior = 0.0f;
	tiempoActual = 0.0f;
	tiempoDiferencial = 0.0f;

	coordenadas = vec3(0.0f, 0.0f, 0.0f);

	//Establece el valor como una matriz identidad
	transformaciones = mat4(1.0f);

	Vertice v1 = {
		vec4(0.0f, 0.1f, 0.0f, 1.0f),
		vec4(1.0f, 0.0f, 0.0f, 1.0f)
	};

	Vertice v2 = {
		vec4(-0.1f, -0.1f, 0.0f, 1.0f),
		vec4(1.0f, 0.8f, 0.0f, 1.0f)
	};

	Vertice v3 = {
		vec4(0.1f, -0.1f, 0.0f, 1.0f),
		vec4(1.0f, 0.8f, 0.0f, 1.0f)
	};

	vertices.push_back(v1);
	vertices.push_back(v2);
	vertices.push_back(v3);

}

void Nave::rotar(Direccion direccion) {

	float rotacion = velocidadAngular;
	if(direccion == Direccion::Derecha){

		rotacion = -rotacion;
	
	}
	angulo += rotacion;

}

void Nave::avanzar(Direccion direccion) {

	
	/*if (estadoAbajo == GLFW_PRESS) {

	//nave->avanzar();
	yTriangulo -= velocidad * tiempoDiferencial;
	}*/
	
	float anguloDesfasado = angulo + 90.0f;

	xTriangulo = cos(anguloDesfasado * 3.14159f / 180.0f) * velocidad * tiempoDiferencial;
	yTriangulo = sin(anguloDesfasado * 3.14159f / 180.0f) * velocidad * tiempoDiferencial;

	if (xTriangulo < -1.1f) {
		xTriangulo += 2.0f;
	}
	else if (xTriangulo > 1.1f) {
		xTriangulo -= 2.0f;
	}

	if (yTriangulo < -1.1f) {
		yTriangulo += 2.0f;
	}
	else if (yTriangulo > 1.1f) {
		yTriangulo -= 2.0f;
	}	

	vec3 traslacion = vec3(
		xTriangulo, //x
		yTriangulo, //y
		0.0f //z
	);

	coordenadas += traslacion;

	actualizarMatrizTransformacion();
	
}


void Nave::actualizarMatrizTransformacion() {
	
	//Partir siempre de una matriz identidad
	transformaciones = mat4(1.0f);
	//Aplicar las transformaciones
	transformaciones = translate(transformaciones, coordenadas);
	transformaciones = rotate(transformaciones, (angulo * 3.14159f / 180.0f), vec3(0.0f, 0.0f, 1.0f));
	

}
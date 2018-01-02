#include "matrix3.h"


// #### METHODES DE LA CLASSE : ml::version3::matrix #### //

ml::version3::matrix::matrix(const std::size_t L, const std::size_t C){ // Y: pour les lignes et X pour les colonnes.

	assert(C > 0 && L > 0);
	this->columns = C;
	this->lines = L;
	// Allocation mémoire du tableau
	mat = new double*[L];
	for(auto i=0; i<L; i++){
		mat[i] = new double[C];
	}
	// On initialise la matrice à 0.
	for(auto i= 0; i < L ; i++) {
		for(auto j= 0; j < C ; j++) {
			mat[i][j] = 0;
		}
	}
}
ml::version3::matrix::matrix(const ml::version3::matrix& m){
	this->columns = m.cols();
	this->lines = m.rows();
	mat = new double*[this->lines];
	for(auto i=0; i<this->lines; i++){
		mat[i] = new double[this->columns];
	}

	for ( auto i = 0; i < m.rows(); i++){
		for ( auto j = 0; j < m.cols(); j++){
	 		mat[i][j] = m(i,j);
	 	}
	}
}

ml::version3::matrix::~matrix(){
	for(auto j= 0; j < this->lines ; j++) {
		delete [] mat[j];
	}
	delete[] mat;
}

std::size_t ml::version3::matrix::cols() const{ return this->columns;}
std::size_t ml::version3::matrix::rows() const{ return this->lines;}

double& ml::version3::matrix::operator()(const std::size_t i, const std::size_t j){
	assert( i < rows() && i >= 0 && j < cols() && j >= 0); // On vérifie les bornes du tableaux
	return mat[i][j];
}
const double& ml::version3::matrix::operator()(const std::size_t i, const std::size_t j) const{
	assert( i < rows() && i >= 0 && j < cols() && j >= 0); // On vérifie les bornes du tableaux
	return mat[i][j];
}

ml::version3::matrix& ml::version3::matrix::operator=(double a){
	for( auto i= 0; i < this->lines; i++){
		for(auto j=0; j < this->columns; j++){
			mat[i][j] = a;
		}
	}
	return *this;
}

ml::vector ml::version3::matrix::operator*(const ml::vector& v) const{
	assert(this->columns == v.size()); // Assert pour vérifier si on peut bien faire la multiplication.
	ml::vector v2(this->lines); // Nouvelle matrice de taille this.y * m1.x
	int i, j;

	for (i = 0; i < v2.size(); i++){
		v2[i] = 0;
		for(j = 0; j < this->columns; j++){
			v2[i] = v2[i] + mat[i][j]*v[j];
		}
	}
	return v2;
}

std::ostream& ml::version3::operator<<(std::ostream& flux, const ml::version3::matrix& m){
	for( auto i= 0; i < m.rows(); i++){
			flux << "[ ";
			for (auto j = 0; j < m.cols(); j++){
				flux << m(i,j) << "  ";
			}
			flux << "]" << std::endl;
		}
	return flux;
}

auto ml::version3::matrix::transpose() -> ml::version3::matrix::transpose_matrix {
	return 	ml::version3::matrix::transpose_matrix(this);
}


//#### #### METHODES DE LA CLASSE : ml:version3::matrix::matrix_transpose ####//

ml::version3::matrix::transpose_matrix::transpose_matrix( ml::version3::matrix* m) : matrice(m){}
ml::version3::matrix::transpose_matrix::~transpose_matrix(){}
std::size_t ml::version3::matrix::transpose_matrix::cols() const{ return this->matrice->rows();}
std::size_t ml::version3::matrix::transpose_matrix::rows() const { return this->matrice->cols();}

double& ml::version3::matrix::transpose_matrix::operator()(const std::size_t i, const std::size_t j){
	assert( i < rows() && i >= 0 && j < cols() && j >= 0); // On vérifie les bornes du tableaux
	return this->matrice->operator()(j,i);
}

const double& ml::version3::matrix::transpose_matrix::operator()(const std::size_t i, const std::size_t j) const{
	assert( i < rows() && i >= 0 && j < cols() && j >= 0); // On vérifie les bornes du tableaux
	return this->matrice->operator()(j,i);
}
ml::vector ml::version3::matrix::transpose_matrix::operator*(const ml::vector& v) const{
	assert(this->cols() == v.size()); // Assert pour vérifier si on peut bien faire la multiplication.
	ml::vector v2(this->rows()); // Nouvelle matrice de taille this.y * m1.x
	int i, j;

	for (i = 0; i < v2.size(); i++){
		v2[i] = 0;
		for(j = 0; j < this->cols(); j++){
			v2[i] = v2[i] + this->operator()(i,j)*v[j];
		}
	}
	return v2;
}
std::ostream& ml::version3::operator<<(std::ostream& flux, const ml::version3::matrix::transpose_matrix& m){
	for( auto i= 0; i < m.rows(); i++){
			flux << "[ ";
			for (auto j = 0; j < m.cols(); j++){
				flux << m(i,j) << "  ";
			}
			flux << "]" << std::endl;
		}
	return flux;
}


#include <fstream>
#include <string>
#include "master_slave.cpp"

int main(int argc, char** argv){

    int opt;
    int iter;
    unsigned long int n, max, min;
    bool first_time = false;
    bool all_test_flag = false;
    bool aks_flag = false;
    bool euclide_flag = false;
    bool modulo_flag = false;
    bool mem_bound_flag = false;
    bool pock_flag = false;
    bool miller_flag = false;
    bool highly_composite_def_flag = false;
    bool highly_composite_naive_flag = false;

    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == MASTER_RANK){
        //Check si il existe des arguments, si oui recupère le nom du fichier et le nombre d'iterations
        if ( (argc <= 1) || argc > 3 || (argv[argc-1][0] == '-') ) {
            std::cerr << "No argument provided!" << std::endl;
            return 1;
        }
        else {
            iter = atoi(argv[1]);
            std::ifstream f_entree(argv[2], std::ios::in);

            // Comptage du nombre de lignes d'un fichier //
            int size_data = 0;
            std::string line;
            while(getline(f_entree, line)){
                ++size_data;
            }
            // Remplissage du tableau
            unsigned long int* data = new unsigned long int [size_data];
            for(int i = 0; i < size_data ; i++){
                f_entree >> data[i];
            }
             f_entree.close();
            run_master(size-1, data, size_data);
            delete[] data;
        }
    }
    else{
        iter = atoi(argv[1]);
        // Empeche GetOpt d'afficher des erreurs:
        opterr = 0;
        // On récupère les options (doit être connu par tout les processus sauf le maitre qui ne les utilises pas)
        while ( (opt = getopt(argc, argv, "akeoumpihH")) != -1 ) {    // for each option...
            switch ( opt ) {
                case 'a':
                all_test_flag = true;
                break;
                case 'k':
                aks_flag = true;
                break;
                case 'e':
                euclide_flag = true;
                break;
                case 'o':
                modulo_flag = true;
                break;
                case 'm':
                mem_bound_flag = true;
                break;
                case 'p':
                pock_flag = true;
                break;
                case 'i':
                miller_flag = true;
                break;
                case 'h':
                highly_composite_naive_flag = true;
                break;
                case 'H':
                highly_composite_def_flag = true;
                break;
                case '?': // option inconnue
                std::cerr << "Unknown option: '" << char(optopt) << "'!" << std::endl;
                break;
            }
        }
        run_slave(rank, iter, first_time, all_test_flag, aks_flag, euclide_flag, modulo_flag, mem_bound_flag,
            pock_flag, miller_flag, highly_composite_def_flag, highly_composite_naive_flag);
        }

        MPI_Finalize();
        //Fin du programme
        return 0;
    }

#include "grman/grman.h"
#include <iostream>

#include "graph.h"

int main()
{
    /// A appeler en 1er avant d'instancier des objets graphiques etc...
    grman::init();

    /// Le nom du répertoire où se trouvent les images à charger
    grman::set_pictures_path("pics");

    /// Un exemple de graphe
    Graph g;
    //Thing t;

    int choix;

    std::cout << "Quel reseau voulez-vous afficher ?" << std::endl;
    std::cout << "Choix 1 : Petit reseau foret. " << std::endl << "Choix 2 : Grand reseau foret. " << std::endl;
    std::cout << "Choix 3 : Reseau marin. " << std::endl;
    std::cin >> choix;

    std::string a;
    //int b;
    //int c;

    if(choix==1)
    {
        a = "fichpetit.txt";
        //b = 13;
        //c = 7;
    }

    else if(choix==2)
    {
        a = "fichgrand.txt";
        //b = 30;
        //c = 12;
    }

    else if(choix==3)
    {
        a = "fichmarin.txt";
        //b = 16;
        //c = 8;
    }

    else
    {
        std::cout << std::endl << "Votre saisie est erronee. " << std::endl;
    }

    /*std::string a = "fichpetit.txt";
    int b = 13;
    int c = 7;*/
    g.make_example(a);

    /*if(key[KEY_D])
    {
        g.make_example("fichmarin.txt",16,8);
    }

    if(key[KEY_E])
    {
        g.make_example("fichgrand.txt",30,12);
    }*/




    /// Vous gardez la main sur la "boucle de jeu"
    /// ( contrairement à des frameworks plus avancés )
    while ( !key[KEY_ESC] )
    {

        /*if(key[KEY_D])
        {


            int choix;

    std::cout << "Quel reseau voulez-vous afficher ?" << std::endl;
    std::cout << "Choix 1 : Petit reseau foret. " << std::endl << "Choix 2 : Grand reseau foret. " << std::endl;
    std::cout << "Choix 3 : Reseau marin. " << std::endl;
    std::cin >> choix;

    std::string a;
    int b;
    int c;

    if(choix==1)
    {
        a = "fichpetit.txt";
        b = 13;
        c = 7;
    }

    else if(choix==2)
    {
        a = "fichgrand.txt";
        b = 30;
        c = 12;
    }

    else if(choix==3)
    {
        a = "fichmarin.txt";
        b = 16;
        c = 8;
    }

    else
    {
        std::cout << std::endl << "Votre saisie est erronee. " << std::endl;
    }

    std::string a = "fichpetit.txt";
    int b = 13;
    int c = 7;*/
    //g.make_example(a,b,c);
    /*g.make_example("fichmarin.txt",16,8);
        }

        if(key[KEY_E])
        {
            g.make_example("fichgrand.txt",30,12);
        }*/
        /// Il faut appeler les méthodes d'update des objets qui comportent des widgets

        g.update();

        //t.update();

        /// Mise à jour générale (clavier/souris/buffer etc...)
        grman::mettre_a_jour();
        g.sauvegarder(a);
    }

    //g.sauvegarder(a);
    grman::fermer_allegro();


    return 0;
}
END_OF_MAIN();



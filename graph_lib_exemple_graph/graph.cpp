#include "graph.h"
#include <fstream>

/***************************************************
                    VERTEX
****************************************************/

/// Le constructeur met en place les éléments de l'interface
VertexInterface::VertexInterface(int idx, int x, int y, std::string pic_name, int pic_idx)
{
    // La boite englobante
    m_top_box.set_pos(x, y);
    m_top_box.set_dim(130, 100);
    m_top_box.set_moveable();

    // Le slider de réglage de valeur
    m_top_box.add_child( m_slider_value );
    m_slider_value.set_range(0.0 , 100.0); // Valeurs arbitraires, à adapter...
    m_slider_value.set_dim(20,80);
    m_slider_value.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Up);

    // Label de visualisation de valeur
    m_top_box.add_child( m_label_value );
    m_label_value.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Down);

    // Une illustration...
    if (pic_name!="")
    {
        m_top_box.add_child( m_img );
        m_img.set_pic_name(pic_name);
        m_img.set_pic_idx(pic_idx);
        m_img.set_gravity_x(grman::GravityX::Right);
    }

    // Label de visualisation d'index du sommet dans une boite
    m_top_box.add_child( m_box_label_idx );
    m_box_label_idx.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Down);
    m_box_label_idx.set_dim(20,12);
    m_box_label_idx.set_bg_color(BLANC);

    m_box_label_idx.add_child( m_label_idx );
    m_label_idx.set_message( std::to_string(idx) );
}


/// Gestion du Vertex avant l'appel à l'interface
void Vertex::pre_update()
{
    if (!m_interface)
        return;

    /// Copier la valeur locale de la donnée m_value vers le slider associé
    m_interface->m_slider_value.set_value(m_value);

    /// Copier la valeur locale de la donnée m_value vers le label sous le slider
    m_interface->m_label_value.set_message( std::to_string( (int)m_value) );
}


/// Gestion du Vertex après l'appel à l'interface
void Vertex::post_update()
{
    if (!m_interface)
        return;

    /// Reprendre la valeur du slider dans la donnée m_value locale
    m_value = m_interface->m_slider_value.get_value();
}



/***************************************************
                    EDGE
****************************************************/

/// Le constructeur met en place les éléments de l'interface
EdgeInterface::EdgeInterface(Vertex& from, Vertex& to)
{
    // Le WidgetEdge de l'interface de l'arc
    if ( !(from.m_interface && to.m_interface) )
    {
        std::cerr << "Error creating EdgeInterface between vertices having no interface" << std::endl;
        throw "Bad EdgeInterface instanciation";
    }
    m_top_edge.attach_from(from.m_interface->m_top_box);
    m_top_edge.attach_to(to.m_interface->m_top_box);
    m_top_edge.reset_arrow_with_bullet();

    // Une boite pour englober les widgets de réglage associés
    m_top_edge.add_child(m_box_edge);
    m_box_edge.set_dim(24,60);
    m_box_edge.set_bg_color(BLANCBLEU);

    // Le slider de réglage de valeur
    m_box_edge.add_child( m_slider_weight );
    m_slider_weight.set_range(0.0 , 100.0); // Valeurs arbitraires, à adapter...
    m_slider_weight.set_dim(16,40);
    m_slider_weight.set_gravity_y(grman::GravityY::Up);

    // Label de visualisation de valeur
    m_box_edge.add_child( m_label_weight );
    m_label_weight.set_gravity_y(grman::GravityY::Down);

}


/// Gestion du Edge avant l'appel à l'interface
void Edge::pre_update()
{
    if (!m_interface)
        return;

    /// Copier la valeur locale de la donnée m_weight vers le slider associé
    m_interface->m_slider_weight.set_value(m_weight);

    /// Copier la valeur locale de la donnée m_weight vers le label sous le slider
    m_interface->m_label_weight.set_message( std::to_string( (int)m_weight ) );
}

/// Gestion du Edge après l'appel à l'interface
void Edge::post_update()
{
    if (!m_interface)
        return;

    /// Reprendre la valeur du slider dans la donnée m_weight locale
    m_weight = m_interface->m_slider_weight.get_value();
}



/***************************************************
                    GRAPH
****************************************************/

/// Ici le constructeur se contente de préparer un cadre d'accueil des
/// éléments qui seront ensuite ajoutés lors de la mise ne place du Graphe
GraphInterface::GraphInterface(int x, int y, int w, int h)
{
    m_top_box.set_dim(1000,740);
    m_top_box.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);

    m_top_box.add_child(m_tool_box);
    m_tool_box.set_dim(80,720);
    m_tool_box.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Up);
    m_tool_box.set_bg_color(BLANCBLEU);

    m_top_box.add_child(m_main_box);
    m_main_box.set_dim(908,720);
    m_main_box.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);
    m_main_box.set_bg_color(BLANCJAUNE);

    m_tool_box.add_child( m_boite_boutons );
    m_boite_boutons.set_dim(60,60);
    m_boite_boutons.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Center );
    m_boite_boutons.set_bg_color(FUCHSIACLAIR);
    m_boite_boutons.set_moveable();

    m_boite_boutons.add_child( m_bouton1 );
    m_bouton1.set_frame(3,3,32,16);
    m_bouton1.set_bg_color(FUCHSIA);

    m_bouton1.add_child(m_bouton1_label);
    m_bouton1_label.set_message("NEW");


}


/// Méthode spéciale qui construit un graphe arbitraire (démo)
/// Cette méthode est à enlever et remplacer par un système
/// de chargement de fichiers par exemple.
/// Bien sûr on ne veut pas que vos graphes soient construits
/// "à la main" dans le code comme ça.
void Graph::make_example(std::string a)
{
    m_interface = std::make_shared<GraphInterface>(50, 0, 750, 600);
    std::ifstream fichier(a, std::ios::in);

    int indiceEdge, posx, posy, vertexin, vertexout, indiceVertex;
    double poidEdge, poidVertex;
    std::string picname;

    if(fichier)
    {
        fichier >> Graph::ordre;
        fichier >> Graph::nbrEdge;
        std::cout << nbrEdge;

        for(int i=0; i < ordre; i++)
        {
            fichier >> poidVertex;
            fichier >> posx;
            fichier >> posy;
            fichier >> picname;

            add_interfaced_vertex(i,poidVertex,posx,posy,picname);

        }

        for (int j=0; j<nbrEdge; j++)
        {
            fichier >> vertexin;
            fichier >> vertexout;
            fichier >> poidEdge;
            add_interfaced_edge(j,vertexin,vertexout,poidEdge);
        }

        fichier.close();

    }

    // La ligne précédente est en gros équivalente à :
    // m_interface = new GraphInterface(50, 0, 750, 600);

    /// Les sommets doivent être définis avant les arcs
    // Ajouter le sommet d'indice 0 de valeur 30 en x=200 et y=100 avec l'image clown1.jpg etc...

    /*int k,m,n,q,r,s;
    double l,t;
    std::string o;
    std::ifstream fichier(a, std::ios::in);

    if(fichier)
    {
        for(int i=0; i<b; i++)
        {
            if(i<c)
            {
                fichier >> k;
                fichier >> l;
                fichier >> m;
                fichier >> n;
                fichier >> o;


                    add_interfaced_vertex(k, l, m, n, o);


            }
            else
            {
                fichier >> q;
                fichier >> r;
                fichier >> s;
                fichier >> t;

                add_interfaced_edge(q, r, s, t);
            }
        }
    }

    fichier.close();*/

    //add_interfaced_vertex(k, l, m, n, "clown1.jpg");
    /*add_interfaced_vertex(0, 30.0, 200, 100, "clown1.jpg");
    add_interfaced_vertex(1, 60.0, 400, 100, "clown2.jpg");
    add_interfaced_vertex(2,  50.0, 200, 300, "clown3.jpg");
    add_interfaced_vertex(3,  0.0, 400, 300, "clown4.jpg");
    add_interfaced_vertex(4,  100.0, 600, 300, "clown5.jpg");
    add_interfaced_vertex(5,  0.0, 100, 500, "bad_clowns_xx3xx.jpg", 0);
    add_interfaced_vertex(6,  0.0, 300, 500, "bad_clowns_xx3xx.jpg", 1);
    add_interfaced_vertex(7,  0.0, 500, 500, "bad_clowns_xx3xx.jpg", 2);*/

        /// Les arcs doivent être définis entre des sommets qui existent !
    // AJouter l'arc d'indice 0, allant du sommet 1 au sommet 2 de poids 50 etc...
    /*add_interfaced_edge(0, 1, 2, 50.0);
    add_interfaced_edge(1, 0, 1, 50.0);
    add_interfaced_edge(2, 1, 3, 75.0);
    add_interfaced_edge(3, 4, 1, 25.0);
    add_interfaced_edge(4, 6, 3, 25.0);
    add_interfaced_edge(5, 7, 3, 25.0);
    add_interfaced_edge(6, 3, 4, 0.0);
    add_interfaced_edge(7, 2, 0, 100.0);
    add_interfaced_edge(8, 5, 2, 20.0);
    add_interfaced_edge(9, 3, 7, 80.0);*/
}

/// La méthode update à appeler dans la boucle de jeu pour les graphes avec interface
void Graph::update()
{
    //m_tool_box.update();
    //make_example("fichpetit.txt",13,7);

    if (!m_interface)
        return;


    for (auto &elt : m_vertices)
        elt.second.pre_update();

    for (auto &elt : m_edges)
        elt.second.pre_update();

    m_interface->m_top_box.update();

    for (auto &elt : m_vertices)
        elt.second.post_update();

    for (auto &elt : m_edges)
        elt.second.post_update();

        /*if ( m_bouton1.clicked() )
    {
        std::cout << "NEW !" << std::endl;

        make_example("fichgrand.txt",30,12);
    }*/

}

/// Aide à l'ajout de sommets interfacés
void Graph::add_interfaced_vertex(int idx, double value, int x, int y, std::string pic_name, int pic_idx )
{
    if ( m_vertices.find(idx)!=m_vertices.end() )
    {
        std::cerr << "Error adding vertex at idx=" << idx << " already used..." << std::endl;
        throw "Error adding vertex";
    }
    // Création d'une interface de sommet
    VertexInterface *vi = new VertexInterface(idx, x, y, pic_name, pic_idx);
    // Ajout de la top box de l'interface de sommet
    m_interface->m_main_box.add_child(vi->m_top_box);
    // On peut ajouter directement des vertices dans la map avec la notation crochet :
    m_vertices[idx] = Vertex(value, vi);
}

/// Aide à l'ajout d'arcs interfacés
void Graph::add_interfaced_edge(int idx, int id_vert1, int id_vert2, double weight)
{
    if ( m_edges.find(idx)!=m_edges.end() )
    {
        std::cerr << "Error adding edge at idx=" << idx << " already used..." << std::endl;
        throw "Error adding edge";
    }

    if ( m_vertices.find(id_vert1)==m_vertices.end() || m_vertices.find(id_vert2)==m_vertices.end() )
    {
        std::cerr << "Error adding edge idx=" << idx << " between vertices " << id_vert1 << " and " << id_vert2 << " not in m_vertices" << std::endl;
        throw "Error adding edge";
    }

    EdgeInterface *ei = new EdgeInterface(m_vertices[id_vert1], m_vertices[id_vert2]);
    m_interface->m_main_box.add_child(ei->m_top_edge);
    m_edges[idx] = Edge(weight, ei);

    m_edges[idx].m_from = id_vert1;

    m_edges[idx].m_to = id_vert2;



    m_vertices[id_vert1].m_out.push_back(idx);

    m_vertices[id_vert2].m_in.push_back(idx);
}

/*Thing::Thing()
{
    m_main_box.add_child( m_lien2 );
    m_lien2.attach_from(m_boite_boutons);
    //m_lien2.attach_to(m_img_anime);
    //m_lien2.reset_arrow_with_bullet();

    m_lien2.add_child( m_lien2_label );
    m_lien2_label.set_message("RIEN");

    m_main_box.add_child( m_boite_boutons );
    m_boite_boutons.set_dim(60,60);
    m_boite_boutons.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up );
    m_boite_boutons.set_bg_color(FUCHSIACLAIR);
    m_boite_boutons.set_moveable();

    /*m_boite_boutons.add_child( m_bouton1 );
    m_bouton1.set_frame(3,3,32,16);
    m_bouton1.set_bg_color(FUCHSIA);

    m_bouton1.add_child(m_bouton1_label);
    m_bouton1_label.set_message("NEW");

}*/

/*void Thing::update()
{

    /// Si tous les widgets dépendants de l'objet sont dans une top box
    /// alors ce seul appel suffit (la propagation d'updates se fait ensuite automatiquement)
    m_top_box.update();

}

Thing::~Thing()
{
    while ( !m_dynaclowns.empty() )
    {
        delete m_dynaclowns.top();
        m_dynaclowns.pop();
    }
}
*/



void Graph::sauvegarder(std::string a)
{
    std::ofstream fichier(a, std::ios::out | std::ios::trunc);
    std::string picname;

    if(fichier)
    {
        fichier << Graph::ordre << std::endl;
        fichier << Graph::nbrEdge << std::endl;

        for (auto &elt : m_vertices)
        {
            fichier << elt.second.m_value << " ";
            fichier << elt.second.m_interface->m_top_box.get_frame_pos().x<<" ";
            fichier << elt.second.m_interface->m_top_box.get_frame_pos().y<<" ";
            picname=elt.second.m_interface->m_img.get_picname();
            picname.erase(picname.size()-4,4);
            fichier << picname + ".jpg" << std::endl;

        }

        for (auto &elt : m_edges)
        {
            fichier << elt.second.m_from<<" ";
            fichier << elt.second.m_to<<" ";
            fichier << elt.second.m_weight << std::endl;
        }
        fichier.close();
        //std::cout << "Sauvegarde faite.";
    }
}

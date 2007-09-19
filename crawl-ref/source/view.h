/*
 *  File:       view.cc
 *  Summary:    Misc function used to render the dungeon.
 *  Written by: Linley Henzell
 *
 *  Modified for Crawl Reference by $Author$ on $Date$
 *
 *  Change History (most recent first):
 *
 *     <2>     9/29/99     BCR     Added the BORDER_COLOR define
 *     <1>     -/--/--     LRH     Created
 */


#ifndef VIEW_H
#define VIEW_H


#include "externs.h"

// various elemental colour schemes... used for abstracting random short lists
// MUST match the order in initfile.cc or breakage results.
enum element_type
{
    EC_FIRE = 32,       // fiery colours (must be first and > highest colour)
    EC_ICE,             // icy colours
    EC_EARTH,           // earthy colours
    EC_ELECTRICITY,     // electrical side of air
    EC_AIR,             // non-electric and general air magic
    EC_POISON,          // used only for venom mage and stalker stuff
    EC_WATER,           // used only for the elemental
    EC_MAGIC,           // general magical effect
    EC_MUTAGENIC,       // transmute, poly, radiation effects
    EC_WARP,            // teleportation and anything similar
    EC_ENCHANT,         // magical enhancements
    EC_HEAL,            // holy healing (not necromantic stuff)
    EC_HOLY,            // general "good" god effects
    EC_DARK,            // darkness
    EC_DEATH,           // currently only assassin (and equal to EC_NECRO)
    EC_NECRO,           // necromancy stuff
    EC_UNHOLY,          // demonology stuff
    EC_VEHUMET,         // vehumet's odd-ball colours
    EC_BEOGH,           // Beogh altar colours
    EC_CRYSTAL,         // colours of crystal
    EC_BLOOD,           // colours of blood
    EC_SMOKE,           // colours of smoke
    EC_SLIME,           // colours of slime
    EC_JEWEL,           // colourful 
    EC_ELVEN,           // used for colouring elf fabric items
    EC_DWARVEN,         // used for colouring dwarf fabric items
    EC_ORCISH,          // used for colouring orc fabric items
    EC_GILA,            // gila monster colours
    EC_FLOOR,           // colour of the area's floor
    EC_ROCK,            // colour of the area's rock
    EC_STONE,           // colour of the area's stone
    EC_MIST,            // colour of mist
    EC_SHIMMER_BLUE,    // shimmering colours of blue.
    EC_RANDOM           // any colour (except BLACK)
};

#define BORDER_COLOR BROWN

void init_char_table(char_set_type set);
void init_feature_table();
void init_monsters_seens();

// last updated 29may2000 {dlb}
/* ***********************************************************************
 * called from: bang - beam - direct - effects - fight - monstuff -
 *              mstuff2 - spells1 - spells2
 * *********************************************************************** */
bool mons_near(const monsters *monster, unsigned int foe = MHITYOU);


// last updated 12may2000 {dlb}
/* ***********************************************************************
 * called from: acr - player - stuff
 * *********************************************************************** */
void draw_border(void);

// last updated 12may2000 {dlb}
/* ***********************************************************************
 * called from: acr - view
 * *********************************************************************** */
void item(void);

void find_features(const std::vector<coord_def>& features,
        unsigned char feature, std::vector<coord_def> *found);

// last updated 12may2000 {dlb}
/* ***********************************************************************
 * called from: direct - monstufff - view
 * *********************************************************************** */
void losight(FixedArray<unsigned int, ENV_SHOW_DIAMETER, ENV_SHOW_DIAMETER>& sh,
             FixedArray<dungeon_feature_type, GXM, GYM>& gr,
             int x_p, int y_p);


bool magic_mapping(int map_radius, int proportion, bool suppress_msg,
                   bool force = false);


// last updated 12may2000 {dlb}
/* ***********************************************************************
 * called from: acr - effects - it_use2 - it_use3 - item_use - spell -
 *              spells - spells3 - spells4
 * *********************************************************************** */
bool noisy( int loudness, int nois_x, int nois_y, const char *msg = NULL );


// last updated 12may2000 {dlb}
/* ***********************************************************************
 * called from: acr - spells3
 * *********************************************************************** */
void show_map( FixedVector<int, 2>& spec_place, bool travel_mode );

// last updated 19jun2000 (gdl)
/* ***********************************************************************
 * called from: acr view
 * *********************************************************************** */
void setLOSRadius(int newLR);

// last updated 02apr2001 (gdl)
/* ***********************************************************************
 * called from: view monstuff
 * *********************************************************************** */
bool check_awaken(monsters* monster);

void clear_map(bool clear_items = true, bool clear_mons = true);

bool is_feature(int feature, int x, int y);

void get_item_glyph(const item_def *item, unsigned *glych,
                    unsigned short *glycol);
void get_mons_glyph(const monsters *mons, unsigned *glych,
                    unsigned short *glycol);
unsigned get_screen_glyph( int x, int y );
std::string stringize_glyph(unsigned glyph);
int multibyte_strlen(const std::string &s);

void get_item_symbol(unsigned int object, unsigned *ch,
                     unsigned short *colour);

// Applies EC_ colour substitutions and brands.
unsigned real_colour(unsigned raw_colour);
int get_mons_colour(const monsters *mons);

const feature_def &get_feature_def(dungeon_feature_type feat);

void set_envmap_obj( int x, int y, int object );
unsigned get_envmap_char(int x, int y);
int get_envmap_obj(int x, int y);
void set_envmap_detected_item(int x, int y, bool detected = true);
void set_envmap_detected_mons(int x, int y, bool detected = true);
void set_envmap_col( int x, int y, int colour, int flags );
void set_envmap_col( int x, int y, int colour );

bool is_envmap_detected_item(int x, int y);
bool is_envmap_detected_mons(int x, int y);
void set_terrain_mapped( int x, int y );
void set_terrain_seen( int x, int y );
void set_terrain_changed( int x, int y );
bool is_terrain_known( int x, int y );
bool is_terrain_seen( int x, int y );
bool is_terrain_changed( int x, int y );
bool is_terrain_known(const coord_def &p);
bool is_notable_terrain(dungeon_feature_type ftype);

inline bool is_terrain_seen(const coord_def &c)
{
    return (is_terrain_seen(c.x, c.y));
}

inline void set_terrain_changed(const coord_def &c)
{
    set_terrain_changed(c.x, c.y);
}

void clear_feature_overrides();
void add_feature_override(const std::string &text);
void clear_cset_overrides();
void add_cset_override(char_set_type set, const std::string &overrides);

bool see_grid( int grx, int gry );
inline bool see_grid(const coord_def &p) { return see_grid(p.x, p.y); }

std::string screenshot(bool fullscreen = false);

unsigned get_sightmap_char(int feature);
unsigned get_magicmap_char(int feature);

bool view_update();
void view_update_at(const coord_def &pos);
void viewwindow(bool draw_it, bool do_updates);
void fire_monster_alerts();

struct ray_def;
bool find_ray( int sourcex, int sourcey, int targetx, int targety,
               bool allow_fallback, ray_def& ray, int cycle_dir = 0,
               bool find_shortest = false );

dungeon_char_type dchar_by_name(const std::string &name);

void handle_terminal_resize(bool redraw = true);

#if defined(WIN32CONSOLE) || defined(DOS)
unsigned short dos_brand( unsigned short colour,
                          unsigned brand = CHATTR_REVERSE);
#endif

#endif

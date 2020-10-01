/****************************************************
 * Created by Marcin "Stas" Sokołowski              *
 * DbD Log Reader to get/store information          *
 * about killer, offerings, some of killers perks   *
 * and amount of hooks.                             *
 * DBD_log_reader v 0.2.5                           *
 ****************************************************/

#include <iostream>
#include <chrono>
#include <thread>
#include <fstream>
#include <string>
#include <list>

int main()
{
    std::cout << "DBD_log_reader v 0.2.5\n\nBy: Marcin 'Stas' Sokolowski\n\n";
    std::string USERPROFILE{ "C:\\Users\\" };
    std::string USER{ "" };
    std::cout << "Your USER name: ";
    try {
        std::getline(std::cin, USER);
        USERPROFILE += USER + "\\AppData\\Local\\DeadByDaylight\\Saved\\Logs\\DeadByDaylight.log";
    }
    catch (std::length_error & le) {
        std::cerr << "Length error: " << le.what() << "\n";
        return 1;
    }
    std::ifstream ifs{ USERPROFILE };
    std::chrono::seconds dura(2); // Duration of sleep

    if (ifs.is_open()) {
        std::cout << "\nFile opened..." << std::endl;
        std::string line{ "" };
        std::string info{ "" };

        std::string query{ "" };
        std::size_t found_line_info_p{ std::string::npos };

        bool killer_found = false;
        bool killer_changed = false;
        bool killer_shown = false;

        enum Killers {Trapper, Wraith, Billy, Nurse, Huntress, Myers, Hag, Doctor, Bubba, Freddy, Pig, Clown, Spirit, Legion, Plague, GhostFace, Demogorgon, Oni, Deathslinger};
        const char* killers_list[] { "Trapper", "Wraith", "Billy", "Nurse", "Huntress", "Myers", "Hag", "Doctor", "Bubba", "Freddy", "Pig", "Clown", "Spirit", "Legion", "Plague", "GhostFace", "Demogorgon", "Oni", "Deathslinger" };
        int actual_killer{ 0 };
        int actual_killer_to_table{ 0 };
        int prev_killer{ 0 };

        bool b_hooks = false;
        bool b_pallets = false;

        int hooks{ 0 };
        int pallets{ 0 };

        int nurse_calling{ 0 };

        while (true)
        {
            //Read every line until EOF
            while (std::getline(ifs, line)) {
                //CODE TO PERFORM OPERATIONS WITH INFO FROM OPENED FILE

                //Startup info
                query = "LogInit: ";
                found_line_info_p = line.find(query); //position of fisrt appearance in line
                if (found_line_info_p != std::string::npos) {
                    info = { line, found_line_info_p + query.size() , std::string::npos };
                    std::cout << "Init info: " << info << std::endl;
                }
                // */

                //Killer info
                query = "LogCustomization: --> ";
                found_line_info_p = line.find(query); //position
                if (found_line_info_p != std::string::npos) { //Found info : SURV or KILLER, but searching just which killer it is
                    info = { line, found_line_info_p + query.size() , 2 }; //taking 2 infos of killer

                    // Logic to decypher killer
                    if ((info == "TR" || info == "S0") && (actual_killer << Killers::Trapper) == 0) {
                        actual_killer = actual_killer << Killers::Trapper;
                        actual_killer_to_table = Killers::Trapper;
                        killer_found = true;
                    }
                    else if ((info == "TW" || info == "Wr") && (actual_killer << Killers::Wraith) == 0){
                        actual_killer = actual_killer << Killers::Wraith;
                        actual_killer_to_table = Killers::Wraith;
                        killer_found = true;
                    }
                    else if ((info == "TC" || info == "Hi") && (actual_killer << Killers::Billy) == 0) {
                        actual_killer = actual_killer << Killers::Billy;
                        actual_killer_to_table = Killers::Billy;
                        killer_found = true;
                    }
                    else if ((info == "TN" || info == "Nu") && (actual_killer << Killers::Nurse) == 0) {
                        actual_killer = actual_killer << Killers::Nurse;
                        actual_killer_to_table = Killers::Nurse;
                        killer_found = true;
                    }
                    else if (info == "BE" && (actual_killer << Killers::Huntress) == 0) {
                        actual_killer = actual_killer << Killers::Huntress;
                        actual_killer_to_table = Killers::Huntress;
                        killer_found = true;
                    }
                    else if (info == "MM" && (actual_killer << Killers::Myers) == 0) {
                        actual_killer = actual_killer << Killers::Myers;
                        actual_killer_to_table = Killers::Myers;
                        killer_found = true;
                    }
                    else if ((info == "HA" || info == "WI") && (actual_killer << Killers::Hag) == 0) {
                        actual_killer = actual_killer << Killers::Hag;
                        actual_killer_to_table = Killers::Hag;
                        killer_found = true;
                    }
                    else if (info == "DO" && (actual_killer << Killers::Doctor) == 0) {
                        actual_killer = actual_killer << Killers::Doctor;
                        actual_killer_to_table = Killers::Doctor;
                        killer_found = true;
                    }
                    else if (info == "CA" && (actual_killer << Killers::Bubba) == 0) {
                        actual_killer = actual_killer << Killers::Bubba;
                        actual_killer_to_table = Killers::Bubba;
                        killer_found = true;
                    }
                    else if (info == "SD" && (actual_killer << Killers::Freddy) == 0) {
                        actual_killer = actual_killer << Killers::Freddy;
                        actual_killer_to_table = Killers::Freddy;
                        killer_found = true;
                    }
                    else if (info == "FK" && (actual_killer << Killers::Pig) == 0) {
                        actual_killer = actual_killer << Killers::Pig;
                        actual_killer_to_table = Killers::Pig;
                        killer_found = true;
                    }
                    else if (info == "GK" && (actual_killer << Killers::Clown) == 0) {
                        actual_killer = actual_killer << Killers::Clown;
                        actual_killer_to_table = Killers::Clown;
                        killer_found = true;
                    }
                    else if (info == "HK" && (actual_killer << Killers::Spirit) == 0) {
                        actual_killer = actual_killer << Killers::Spirit;
                        actual_killer_to_table = Killers::Spirit;
                        killer_found = true;
                    }
                    else if (info == "KK" && (actual_killer << Killers::Legion) == 0) {
                        actual_killer = actual_killer << Killers::Legion;
                        actual_killer_to_table = Killers::Legion;
                        killer_found = true;
                    }
                    else if (info == "MK" && (actual_killer << Killers::Plague) == 0) {
                        actual_killer = actual_killer << Killers::Plague;
                        killer_found = true;
                    }
                    else if (info == "OK" && (actual_killer << Killers::GhostFace) == 0) {
                        actual_killer = actual_killer << Killers::GhostFace;
                        actual_killer_to_table = Killers::GhostFace;
                        killer_found = true;
                    }
                    else if (info == "QK" && (actual_killer << Killers::Demogorgon) == 0) {
                        actual_killer = actual_killer << Killers::Demogorgon;
                        actual_killer_to_table = Killers::Demogorgon;
                        killer_found = true;
                    }
                    else if (info == "Sw" && (actual_killer << Killers::Oni) == 0) {
                        actual_killer = actual_killer << Killers::Oni;
                        actual_killer_to_table = Killers::Oni;
                        killer_found = true;
                    }
                    else if (info == "Uk" && (actual_killer << Killers::Deathslinger) == 0) {
                        actual_killer = actual_killer << Killers::Deathslinger;
                        actual_killer_to_table = Killers::Deathslinger;
                        killer_found = true;
                    }

                    if (prev_killer != actual_killer_to_table) { //killer changed option for updating Killer info display
                        prev_killer = actual_killer_to_table;
                        killer_changed = true;
                    }
                    
                    if (killer_found && (!killer_shown || killer_changed)) {
                        killer_changed = false;
                        killer_shown = true;
                        std::cout << "\nKiller: " << killers_list[actual_killer_to_table] << std::endl;
                    }
                }

                //Offerings
                query = "SendOfferingsDataToUI --> Keep in cache offering ";
                found_line_info_p = line.find(query);
                if (found_line_info_p != std::string::npos) {
                    info = { line, found_line_info_p + query.size() , std::string::npos };
                    std::cout << "\nOffering: " << info << std::endl;
                    killer_found = false;
                    killer_changed = false;
                    killer_shown = false;
                }

                //Count Hooks
                query = "MeatHook Initilized ";
                found_line_info_p = line.find(query);
                if (found_line_info_p != std::string::npos) {
                    hooks += 1;
                    b_hooks = true;
                }
                //Count Pallets 
                query = "PersistentLevel.Bookshelf_C_";
                found_line_info_p = line.find(query);
                if (found_line_info_p != std::string::npos) {
                    pallets += 1;
                    b_pallets = true;
                }

                //NurseCalling
                query = "NurseCalling_Effect";
                found_line_info_p = line.find(query);
                if (found_line_info_p != std::string::npos) {
                    std::cout << "\n!!!!!\nIn range of Nurse Calling id: " << nurse_calling  << "\n!!!!!" << std::endl;
                    ++nurse_calling;
                }

                //Print Hooks and Pallets
                query = "LogActorComponent: RegisterComponentWithWorld: ";
                found_line_info_p = line.find(query);
                if (found_line_info_p != std::string::npos && b_pallets) {
                    std::cout << "\nHooks: " << hooks << std::endl;
                    hooks = 0;
                    b_hooks = false;
                    std::cout << "\nPallets: " << pallets/2 << std::endl;
                    pallets = 0;
                    b_pallets = false;
                    nurse_calling = 0;
                }

                /*//Errors 
                query = " Error: ";
                found_line_info_p = line.find(query);
                if (found_line_info_p != std::string::npos) {
                    info = { line, found_line_info_p + query.size() , std::string::npos };
                    std::cout << "Error: " << info << std::endl;
                }
                // */


            }
            if (!ifs.eof()) break; //Ensure end of file happened
            ifs.clear(); // Clear flags

            // Sleep to avoid bein a CPU hog
            std::this_thread::sleep_for(dura);
        }
    }
    return 0;
}

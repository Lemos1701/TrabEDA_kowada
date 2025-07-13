#include "generateData.h"

const char* cpf_p1[100] = {
    "020066", "032436", "036776", "046828", "049797", "052067", "057840", "060720", "065416", "066827",
    "077429", "082580", "097092", "101447", "107177", "129259", "142233", "146670", "166184", "178973",
    "190635", "197783", "213007", "219737", "246510", "249009", "271363", "276942", "283749", "299363",
    "304459", "310311", "331869", "335179", "352701", "358971", "373665", "384855", "385695", "411796",
    "413542", "436399", "449195", "455853", "473919", "475819", "479367", "482484", "495766", "507264",
    "510821", "511857", "526769", "532543", "537458", "567931", "569910", "576879", "577755", "605817",
    "615063", "618445", "630109", "631061", "654569", "658876", "664334", "664414", "668317", "669283",
    "674794", "676215", "678119", "691343", "691605", "692453", "698127", "702671", "719425", "721734",
    "725255", "735597", "754339", "761849", "765241", "781521", "788761", "791059", "808963", "811452",
    "831170", "831928", "868337", "898946", "900214", "946129", "965690", "967114", "977310", "985226"
};

const char* cpf_p2[100] = {
    "00009", "00109", "00209", "00309", "00409", "00509", "00609", "00709", "00809", "00909",
    "01009", "01109", "01209", "01309", "01409", "01509", "01609", "01709", "01809", "01909",
    "02009", "02109", "02209", "02309", "02409", "02509", "02609", "02709", "02809", "02909",
    "03009", "03109", "03209", "03309", "03409", "03509", "03609", "03709", "03809", "03909",
    "04009", "04109", "04209", "04309", "04409", "04509", "04609", "04709", "04809", "04909",
    "05009", "05109", "05209", "05309", "05409", "05509", "05609", "05709", "05809", "05909",
    "06009", "06109", "06209", "06309", "06409", "06509", "06609", "06709", "06809", "06909",
    "07009", "07109", "07209", "07309", "07409", "07509", "07609", "07709", "07809", "07909",
    "08009", "08109", "08209", "08309", "08409", "08509", "08609", "08709", "08809", "08909",
    "09009", "09109", "09209", "09309", "09409", "09509", "09609", "09709", "09809", "09909"
};

const char* firstname[100] = {
    "Vitor", "Gabriel", "Caio", "Lucas", "Alex", "Miguel",
    "Ana", "Maria", "Júlia", "Beatriz", "Laura", "Helena",
    "Arthur", "Matheus", "Pedro", "João", "Gustavo", "Felipe",
    "Bruno", "Leonardo", "Rafael", "Thiago", "Daniel", "André",
    "Igor", "Eduardo", "Henrique", "Vinicius", "Diego", "Samuel",
    "Isabela", "Sophia", "Valentina", "Lorena", "Yasmin", "Carolina",
    "Mariana", "Lívia", "Giovanna", "Eloá", "Fernanda", "Larissa",
    "Luana", "Clara", "Cecília", "Isadora", "Esther", "Olívia",
    "Elias", "Otávio", "Murilo", "Davi", "Fernando", "Carlos",
    "Marcela", "Melissa", "Paula", "Mirela", "Tatiane", "Luiza",
    "Juliana", "Camila", "Renata", "Elisa", "Daniele", "Patrícia",
    "Sabrina", "Aline", "Vanessa", "Priscila", "Érika", "Milena",
    "Simone", "Bianca", "Adriana", "Cristiane", "Grazi", "Natália",
    "Cael", "Noah", "Yago", "Luiz", "Vicente", "Cristian",
    "Jonathan", "Érico", "Edson", "Israel", "Rian", "Anderson",
    "Mateus", "Emanuel", "Victor", "Raul", "Pablo", "Alan",
    "Renan", "Gilberto", "Valter", "Wellington"
};

const char* lastname[100] = {
    "Lemos", "Baeta", "Conceição", "Duarte", "Gavião", "Guimarães",
    "Ramos", "Silva", "Santos", "Oliveira", "Souza", "Pereira",
    "Lima", "Ferreira", "Almeida", "Costa", "Carvalho", "Rocha",
    "Dias", "Martins", "Barbosa", "Moura", "Melo", "Cavalcante",
    "Batista", "Campos", "Monteiro", "Nogueira", "Teixeira", "Farias",
    "Sales", "Cardoso", "Andrade", "Rezende", "Correia", "Pinto",
    "Azevedo", "Tavares", "Peixoto", "Valverde", "Cunha", "Figueiredo",
    "Vieira", "Antunes", "Castro", "Fonseca", "Pacheco", "Araújo",
    "Seabra", "Assis", "Bittencourt", "Mendes", "Soares", "Queiroz",
    "Amorim", "Amado", "Vasconcelos", "Siqueira", "Ribeiro", "Braga",
    "Magalhães", "Cavalcanti", "Chaves", "Barros", "Porto", "Xavier",
    "Gonçalves", "Esteves", "Bernardes", "Macedo", "Neves", "Pedrosa",
    "Prado", "Freitas", "Camargo", "Maia", "Beltrão", "Brandão",
    "Corrêa", "Coelho", "Diniz", "Siqueira", "Salazar", "Garcia",
    "Moreira", "Borges", "Aguiar", "Barreto", "Lacerda", "Serpa",
    "Machado", "Miranda", "Leal", "Henriques", "Varela", "Saldanha",
    "Torres", "Teles", "Paranhos", "Valadão"
};

void generate_func(FILE* file, const char** name_fp, const char** name_sp, const char** cpf_fp, const char**cpf_sp) {
    if (!file) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }
    rewind(file);

    TS student;

    for(int i = 0; i < 100; i++){
        for(int j = 0; j < 100; j++){
            snprintf(student.name, sizeof(char) * 50, "%s %s", name_fp[i], name_sp[j]);
            
            char aux_cpf[15];
            snprintf(aux_cpf, sizeof(aux_cpf), "%s%s", cpf_fp[i], cpf_sp[j]);
            student.cpf = atoll(aux_cpf);
            
            student.score = rand() % 101;
            fwrite(&student, sizeof(TS), 1, file);
            
            
        }
    }
}
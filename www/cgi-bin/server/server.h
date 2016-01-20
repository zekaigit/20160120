#define MSG_PATH						"/opt"
#define MSG_PROID						2015
#define MSG_CGI_TO_SERVER_TYPE			100
#define MSG_SERVER_TO_CGI_TYPE			200

typedef struct _msg
{
	long mtype;
	char mtext[1024];
}MSG;

#define DB_NAME							"./db/admin.db"
#define GLADE_NAME						"./glade/acs.glade"

#define QUERY_XML						"../../query.xml"

#define UART_RFID						"/dev/ttyUSB0"

#define OK								0
#define NOTOK							1

#define OK_MUSIC						"./music/rfid_right.wav"
#define NOTOK_MUSIC						"./music/rfid_error.wav"

typedef struct _window
{
	GtkWidget *window;
	GtkWidget *label_info;
	GtkWidget *label_name;
	GtkWidget *label_id;
	GtkWidget *label_sex;
	GtkWidget *label_rfid;

}WINDOW;



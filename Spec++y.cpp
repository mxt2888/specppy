#include <gtk/gtk.h>
#include <string>
#include <iostream>
#include <array>
#include <unistd.h>

std::string runCommand(const std::string& cmd) {
    std::array<char, 256> buffer;
    std::string result;
    FILE* pipe = popen(cmd.c_str(), "r");
    if (!pipe) return "Command failed.";
    while (fgets(buffer.data(), buffer.size(), pipe)) {
        result += buffer.data();
    }
    pclose(pipe);
    return result;
}

std::string getGPUDetails() {
    std::string info;
    info += "=== GPU Info from lshw ===\n";
    info += runCommand("lshw -C display");
    info += "\n\n=== OpenGL Info from glxinfo ===\n";
    info += runCommand("glxinfo | grep -E 'OpenGL|render'");
    return info;
}

std::string getMonitorDetails() {
    std::string info;
    info += "=== Monitor Info from xrandr ===\n";
    info += runCommand("xrandr --verbose");
    info += "\n\n=== Decoded EDID Data ===\n";
    std::string decodeCmd =
        "for f in /sys/class/drm/*/edid; do "
        "  echo \"EDID from $f\"; "
        "  edid-decode \"$f\" 2>/dev/null; "
        "done";
    info += runCommand(decodeCmd);
    return info;
}

std::string getOSDetails() {
    std::string info;
    info += "=== lsb_release ===\n";
    info += runCommand("lsb_release -a 2>/dev/null");
    info += "\n=== uname ===\n";
    info += runCommand("uname -a");
    info += "\n=== Kernel Modules ===\n";
    info += runCommand("lsmod");
    info += "\n=== Init System and Target ===\n";
    info += runCommand("systemctl list-units --type=target");
    info += "\n=== System Uptime ===\n";
    info += runCommand("uptime -p");
    info += "\n=== Locale and Environment ===\n";
    info += runCommand("locale");
    info += "\n=== Hostname and Hosts ===\n";
    info += runCommand("hostnamectl");
    info += "\n=== OS Disk Info ===\n";
    info += runCommand("df -h /");
    return info;
}

GtkWidget* create_text_tab(const std::string& label, const std::string& content) {
    GtkWidget *scrolled = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    GtkWidget *textview = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(textview), FALSE);
    gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(textview), FALSE);
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textview));
    gtk_text_buffer_set_text(buffer, content.c_str(), -1);
    gtk_container_add(GTK_CONTAINER(scrolled), textview);
    return scrolled;
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "System Info Viewer (GTK)");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
    GtkWidget *notebook = gtk_notebook_new();
    gtk_container_add(GTK_CONTAINER(window), notebook);
    bool isRoot = geteuid() == 0;

    gtk_notebook_append_page(GTK_NOTEBOOK(notebook),
        create_text_tab("CPU", runCommand("grep 'model name\\|cpu cores\\|vendor_id' /proc/cpuinfo")),
        gtk_label_new("CPU"));

    gtk_notebook_append_page(GTK_NOTEBOOK(notebook),
        create_text_tab("Memory", runCommand("head -n 5 /proc/meminfo")),
        gtk_label_new("Memory"));

    gtk_notebook_append_page(GTK_NOTEBOOK(notebook),
        create_text_tab("Disk", runCommand("df -hT --total")),
        gtk_label_new("Disk"));

    gtk_notebook_append_page(GTK_NOTEBOOK(notebook),
        create_text_tab("Network", runCommand("ip addr")),
        gtk_label_new("Network"));

    gtk_notebook_append_page(GTK_NOTEBOOK(notebook),
        create_text_tab("GPU", getGPUDetails()),
        gtk_label_new("GPU"));

    gtk_notebook_append_page(GTK_NOTEBOOK(notebook),
        create_text_tab("Monitor", getMonitorDetails()),
        gtk_label_new("Monitor"));

    gtk_notebook_append_page(GTK_NOTEBOOK(notebook),
        create_text_tab("OS", getOSDetails()),
        gtk_label_new("OS"));

    if (isRoot) {
        gtk_notebook_append_page(GTK_NOTEBOOK(notebook),
            create_text_tab("BIOS & System", runCommand("dmidecode -t bios -t system")),
            gtk_label_new("BIOS"));

        gtk_notebook_append_page(GTK_NOTEBOOK(notebook),
            create_text_tab("Full Hardware", runCommand("lshw -short")),
            gtk_label_new("Hardware"));

        gtk_notebook_append_page(GTK_NOTEBOOK(notebook),
            create_text_tab("Disk Health", runCommand("for d in /dev/sd?; do echo \"SMART for $d\"; smartctl -H $d; done")),
            gtk_label_new("SMART"));
    }

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}
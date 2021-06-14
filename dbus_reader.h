#ifndef DBUS_READER_H
#define DBUS_READER_H

#include <iostream>
#include <dbus/dbus.h>


using namespace std;


class dbus_reader
{
public:
    dbus_reader();
    bool Connect();
    void Wait_Event();
    bool Is_OnBattery();
    void Prepare_signal();
    void Remove_signal();


private:
    DBusError m_err;
    DBusConnection * m_conn;
    DBusMessage * m_msg;


private:
    double get_double_property(DBusConnection *connection, const char *bus_name, const char *path, const char *iface, const char *propname, DBusError *error);
    bool get_bool_property(DBusConnection *connection, const char *bus_name, const char *path, const char *iface, const char *propname, DBusError *error);
    unsigned int get_uinteger_property(DBusConnection *connection, const char *bus_name, const char *path, const char *iface, const char *propname, DBusError *error);
    double extract_double_from_variant(DBusMessage *reply, DBusError *error);
    bool extract_bool_from_variant(DBusMessage *reply, DBusError *error);
    unsigned int extract_uinteger_from_variant(DBusMessage *reply, DBusError *error);
    DBusMessage *create_property_get_message(const char *bus_name, const char *path, const char *iface, const char *propname);


};

#endif // DBUS_READER_H

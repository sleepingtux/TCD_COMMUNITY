#include "dbus_reader.h"

dbus_reader::dbus_reader()
{

}

double dbus_reader::get_double_property(DBusConnection *connection, const char *bus_name, const char *path, const char *iface, const char *propname, DBusError *error) {
    DBusError myError;
    double result = 0;
    DBusMessage *queryMessage = NULL;
    DBusMessage *replyMessage = NULL;

    dbus_error_init(&myError);

    queryMessage = create_property_get_message(bus_name, path, iface, propname);
    replyMessage = dbus_connection_send_with_reply_and_block(connection,
                          queryMessage,
                          1000,
                          &myError);
    dbus_message_unref(queryMessage);
    if (dbus_error_is_set(&myError)) {
        dbus_move_error(&myError, error);
        return 0;
    }

    result = extract_double_from_variant(replyMessage, &myError);
    if (dbus_error_is_set(&myError)) {
        dbus_move_error(&myError, error);
        return 0;
    }

    dbus_message_unref(replyMessage);

    return result;
 }

bool dbus_reader::get_bool_property(DBusConnection *connection, const char *bus_name, const char *path, const char *iface, const char *propname, DBusError *error) {
    DBusError myError;
    bool result = 0;
    DBusMessage *queryMessage = NULL;
    DBusMessage *replyMessage = NULL;

    dbus_error_init(&myError);

    queryMessage = create_property_get_message(bus_name, path, iface, propname);
    replyMessage = dbus_connection_send_with_reply_and_block(connection,
                          queryMessage,
                          1000,
                          &myError);
    dbus_message_unref(queryMessage);
    if (dbus_error_is_set(&myError)) {
        dbus_move_error(&myError, error);
        return 0;
    }

    result = extract_bool_from_variant(replyMessage, &myError);
    if (dbus_error_is_set(&myError)) {
        dbus_move_error(&myError, error);
        return 0;
    }

    dbus_message_unref(replyMessage);

    return result;
 }

unsigned int dbus_reader::get_uinteger_property(DBusConnection *connection, const char *bus_name, const char *path, const char *iface, const char *propname, DBusError *error) {
    DBusError myError;
    unsigned result = 0;
    DBusMessage *queryMessage = NULL;
    DBusMessage *replyMessage = NULL;

    dbus_error_init(&myError);

    queryMessage = create_property_get_message(bus_name, path, iface, propname);
    replyMessage = dbus_connection_send_with_reply_and_block(connection,
                          queryMessage,
                          1000,
                          &myError);
    dbus_message_unref(queryMessage);
    if (dbus_error_is_set(&myError)) {
        dbus_move_error(&myError, error);
        return 0;
    }

    result = extract_uinteger_from_variant(replyMessage, &myError);
    if (dbus_error_is_set(&myError)) {
        dbus_move_error(&myError, error);
        return 0;
    }

    dbus_message_unref(replyMessage);

    return result;
 }



DBusMessage * dbus_reader::create_property_get_message(const char *bus_name, const char *path, const char *iface, const char *propname) {
    DBusMessage *queryMessage = NULL;

    queryMessage = dbus_message_new_method_call(bus_name, path,
                            "org.freedesktop.DBus.Properties",
                            "Get");
    dbus_message_append_args(queryMessage,
                 DBUS_TYPE_STRING, &iface,
                 DBUS_TYPE_STRING, &propname,
                 DBUS_TYPE_INVALID);

    return queryMessage;
}

double dbus_reader::extract_double_from_variant(DBusMessage *reply, DBusError *error) {
    DBusMessageIter iter;
    DBusMessageIter sub;
    double result;

    dbus_message_iter_init(reply, &iter);

    if (DBUS_TYPE_VARIANT != dbus_message_iter_get_arg_type(&iter)) {
        dbus_set_error_const(error, "reply_should_be_variant", "This message hasn't a variant response type");
        return 0;
    }

    dbus_message_iter_recurse(&iter, &sub);

    if (DBUS_TYPE_DOUBLE != dbus_message_iter_get_arg_type(&sub)) {
        dbus_set_error_const(error, "variant_should_be_double", "This variant reply message must have double content");
        return 0;
    }

    dbus_message_iter_get_basic(&sub, &result);
    return result;
}

bool dbus_reader::extract_bool_from_variant(DBusMessage *reply, DBusError *error) {
    DBusMessageIter iter;
    DBusMessageIter sub;
    bool result;

    dbus_message_iter_init(reply, &iter);

    if (DBUS_TYPE_VARIANT != dbus_message_iter_get_arg_type(&iter)) {
        dbus_set_error_const(error, "reply_should_be_variant", "This message hasn't a variant response type");
        return 0;
    }

    dbus_message_iter_recurse(&iter, &sub);

    if (DBUS_TYPE_BOOLEAN != dbus_message_iter_get_arg_type(&sub)) {
        dbus_set_error_const(error, "variant_should_be_double", "This variant reply message must have double content");
        return 0;
    }

    dbus_message_iter_get_basic(&sub, &result);
    return result;
}


unsigned int dbus_reader::extract_uinteger_from_variant(DBusMessage *reply, DBusError *error) {
    DBusMessageIter iter;
    DBusMessageIter sub;
    unsigned int result;

    dbus_message_iter_init(reply, &iter);

    if (DBUS_TYPE_VARIANT != dbus_message_iter_get_arg_type(&iter)) {
        dbus_set_error_const(error, "reply_should_be_variant", "This message hasn't a variant response type");
        return 0;
    }

    dbus_message_iter_recurse(&iter, &sub);

    if (DBUS_TYPE_UINT32 != dbus_message_iter_get_arg_type(&sub)) {
        dbus_set_error_const(error, "variant_should_be_unsigned_int", "This variant reply message must have unsigned int content");
        return 0;
    }

    dbus_message_iter_get_basic(&sub, &result);
    return result;
}



bool dbus_reader::Connect()
{
    bool returnBool=true;
    dbus_error_init(&m_err);

    // connect to the bus
    m_conn = dbus_bus_get(DBUS_BUS_SYSTEM, &m_err);
    if (dbus_error_is_set(&m_err)) {
         fprintf(stderr, "Connection Error (%s)\n", m_err.message);
         dbus_error_free(&m_err);
         returnBool=false;
     }
     if (NULL == m_conn) {
         returnBool=false;
     }

     return returnBool;
}

void dbus_reader::Prepare_signal()
{
    dbus_bus_add_match(m_conn, "interface='org.freedesktop.DBus.Properties',member='PropertiesChanged',path='/org/freedesktop/UPower',type='signal'", &m_err);
}
void dbus_reader::Remove_signal()
{
    dbus_connection_unref(m_conn);
     //dbus_bus_remove_match(m_conn, "interface='org.freedesktop.DBus.Properties',member='PropertiesChanged',path='/org/freedesktop/UPower',type='signal'", &m_err);
}

void dbus_reader::Wait_Event()
{

    //wait for event
    dbus_connection_read_write(m_conn, -1);
    m_msg = dbus_connection_pop_message(m_conn);

    if (m_msg)
    {
        dbus_message_unref(m_msg);
        //if (dbus_message_is_signal(msg, "org.freedesktop.UPower", "DeviceChanged"))
    }



}

bool dbus_reader::Is_OnBattery()
{
    return get_bool_property(m_conn, "org.freedesktop.UPower",
                             "/org/freedesktop/UPower",
                             "org.freedesktop.UPower",
                             "OnBattery",
                             &m_err);
}

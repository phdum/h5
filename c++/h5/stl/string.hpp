#pragma once
#include "../group.hpp"
#include "../format.hpp"
#include <string>

namespace h5 {

  H5_SPECIALIZE_FORMAT2(std::string, string);

  /**
   * Write a string  into an hdf5 file
   *
   * Format : Fixed size string
   *
   * @tparam T
   * @param g HDF5 group
   * @param name Name of the object in the HDF5 file
   * @param s String to be saved.
   */
  void h5_write(group g, std::string const &name, std::string const &s);

  /**
   * Write a string  into an hdf5 file
   *
   * Format : Fixed size string
   *
   * @tparam T
   * @param g HDF5 group
   * @param name Name of the object in the HDF5 file
   * @param s String to be saved.
   */
  inline void h5_write(group g, std::string const &name, const char *s) { h5_write(g, name, std::string{s}); }

  /**
   * Read a string from an hdf5 file
   *
   * @param f The h5 file or group
   * @param name The name of the hdf5 array in the file/group where the stack will be stored
   * @param value The string to read into
   */
  void h5_read(group g, std::string const &name, std::string &value);

  // Explicitly forbidden.
  inline void h5_read(group g, std::string const &name, char *s) = delete;

  /**
   * Write a string attribute
   *
   * @param f The h5 file or group
   * @param name The name of the hdf5 array in the file/group where the stack will be stored
   * @param s The string.
  */
  void h5_write_attribute(hid_t id, std::string const &name, std::string const &s);

  /**
   * Write a string attribute
   *
   * @param f The h5 file or group
   * @param name The name of the hdf5 array in the file/group where the stack will be stored
   * @param s The string.
  */
  inline void h5_write_attribute(hid_t id, std::string const &name, const char *s) { h5_write_attribute(id, name, std::string{s}); }

  /**
  * Read a string attribute from id.
  * 
  * @param id  The object to which the attribute is attached
  * @param name The name of the attribute
  * @param value The string to fill
  */
  void h5_read_attribute(hid_t id, std::string const &name, std::string &s);

  // forbidden
  inline void h5_read_attribute(hid_t id, std::string const &name, char *s) = delete;

  /**
   * Write a string attribute to a key in an h5::group
   *
   * @param g The h5::group
   * @param key The key
   * @param name The name of the attribute
   * @param s The string attribute
  */
  void h5_write_attribute_to_key(group g, std::string const &key, std::string const &name, std::string const &s);

  /// Write a const char array as a string attribute of a particular key
  inline void h5_write_attribute_to_key(group g, std::string const &key, std::string const &name, const char *s) {
    h5_write_attribute_to_key(g, key, name, std::string{s});
  }

  /**
   * Read a string attribute from a key in an h5::group
   *
   * @param g The h5::group
   * @param key The key
   * @param name The name of the attribute
   * @param s The string to read into
  */
  void h5_read_attribute_from_key(group g, std::string const &key, std::string const &name, std::string &s);

  // ---------------------  hdf5 format -----------------------

  // Write the triqs tag of the group if it is an object.
  template <typename T> void write_hdf5_format(group g, T const &) { write_hdf5_format_as_string(g, get_hdf5_format<T>().c_str()); }

  // ---------------------   char_buf -----------------------

  // char_buf contains an n dimensional array of strings as fixed size strings, flatten in a 1d array of char.
  // the last dimension is the max length of the strings + 1, because of the ending 0 in C !
  struct char_buf {
    std::vector<char> buffer;
    v_t lengths;

    // the string datatype
    [[nodiscard]] datatype dtype() const;

    // the dataspace (without last dim, which is the string).
    [[nodiscard]] dataspace dspace() const;
  };

  // read/write for char_buf
  void h5_write(group g, std::string const &name, char_buf const &cb);
  void h5_write_attribute(hid_t id, std::string const &name, char_buf const &cb);
  void h5_read(group g, std::string const &name, char_buf &_cb);
  void h5_read_attribute(hid_t id, std::string const &name, char_buf &_cb);

} // namespace h5

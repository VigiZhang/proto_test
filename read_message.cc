#include <iostream>
#include <fstream>
#include <fcntl.h>
#include <string>
#include <google/protobuf/text_format.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include "proto/addressbook.pb.h"

using namespace std;

void ListPeople(const proto::AddressBook& address_book) {
  for (int i = 0; i < address_book.people_size(); i++) {
    const proto::Person& person = address_book.people(i);
    cout << "Person ID: " << person.id() << endl;
    cout << "  Name: " << person.name() << endl;
    if (person.has_email()) {
      cout << "  E-mail address: " << person.email() << endl;
    }

    for (int j = 0; j < person.phones_size(); ++j) {
      const proto::Person::PhoneNumber& phone_number = person.phones(j);
      switch (phone_number.type()) {
        case proto::Person::MOBILE:
          cout << "  Mobile phone #: ";
          break;
        case proto::Person::HOME:
          cout << "  Home phone #: ";
          break;
        case proto::Person::WORK:
          cout << "  Work phone #: ";
          break;
      }
      cout << phone_number.number() << endl;
    }
    if (person.name() == "vigi") {
      cout << "vigi was here" << endl;
    } else if (person.name() == "bear") {
      cout << "bear was here" << endl;
    } else {
      cout << "stranger" << endl;
    }
  }
}

int main(int argc, char* argv[]) {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  if (argc != 2) {
    cerr << "Usage: " << argv[0] << " ADDRESS_BOOK_FILE" << endl;
    return -1;
  }

  proto::AddressBook address_book;

  /* {
    fstream input(argv[1], ios::in | ios::binary);
    if (!address_book.ParseFromIstream(&input)) {
      cerr << "Failed to parse address book." << endl;
      return -1;
    }
  } */
  int fd = open(argv[1], O_RDONLY);
  if (fd < 0) {
    cerr << "Error opening the file" << endl;
    return -1;
  }

  google::protobuf::io::FileInputStream fileInput(fd);
  google::protobuf::TextFormat::Parse(&fileInput, &address_book);

  ListPeople(address_book);

  google::protobuf::ShutdownProtobufLibrary();
  return 0;
}

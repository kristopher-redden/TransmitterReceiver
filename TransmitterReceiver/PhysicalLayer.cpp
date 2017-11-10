//
// Created by kristopher on 9/30/17.
//

#include "PhysicalLayer.h"
#include <iostream>
#include <fstream>

void ReadValues();

PhysicalLayer::PhysicalLayer()
{

}

void *get_in_addr(struct sockaddr *sa)
{
    //If AF_INET == IPV4 then we are using protocol IPV4.
    if (sa->sa_family == AF_INET) {//sa_family: address family, of socket address.  IPV4 or IPV6?
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

PhysicalLayer::PhysicalLayer(bool clientTrans, string hostname)
{
    if (clientTrans)
    {
        int numbytes;   // listen on sock_fd
        char buf[MAXDATASIZE + 1];//Add 1 since the last char must be a null char.
        struct addrinfo hints, *servinfo, *p;

        int rv;
        char s[INET6_ADDRSTRLEN]; //Create a char array of size 46 (max length of ipv6 address).

        if (hostname == "") {
            fprintf(stderr,"usage: client hostname\n");
            exit(1);
        }

        memset(&hints, 0, sizeof hints); //Variable, value, size.
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;

        //Needs to return 0 to be successful.
        //Returns a pointer to a linked list.
        if ((rv = getaddrinfo(hostname.c_str(), PORT, &hints, &servinfo)) != 0) {
            fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
            //return 1;
        }

        // loop through all the results and connect to the first we can
        //Grab the first socket that is available.
        for(p = servinfo; p != NULL; p = p->ai_next) {

            if ((sockfd = socket(p->ai_family, p->ai_socktype,
                                 p->ai_protocol)) == -1) {
                perror("client: socket");
                continue;
            }

            if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
                close(sockfd);
                perror("client: connect");
                continue;
            }

            break;
        }

        if (p == NULL) {
            fprintf(stderr, "client: failed to connect\n");
            //return 2;
        }
        inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr),
                  s, sizeof s);
        printf("client: connecting to %s\n", s);\


        freeaddrinfo(servinfo); // all done with this structure
    }
    else {
        //Server
        connectionEstablished = false;

        struct addrinfo hints;
        struct addrinfo *servinfo;
        struct addrinfo *p;


        //Reaps zombie process that appear as the fork();  If you make zombies and don't reap them,
        //your system administrator will become agitated.
        struct sigaction sa;
        int yes = 1;
        int rv;


        memset(&hints, 0, sizeof hints);//Variable, value, size.

        //addrinfo struct
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_flags = AI_PASSIVE; // use my IP
        //addrinfo struct
        //getaddrinfo returns a pointer to a new linked list of these structures filled with info we need.

        //Needs to return 0 to be successful.
        //Returns a pointer to a linked list.
        if ((rv = getaddrinfo(NULL, PORT, &hints, &servinfo)) != 0) {
            fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
            //return 1;
        }

        // loop through all the results and bind to the first we can
        //Grab the first socket that is available.
        for (p = servinfo; p != NULL; p = p->ai_next) {
            //Create a socket, set it to sockfd, if we can't assign to that location
            //we get -1 back.

            if ((sockfd = socket(p->ai_family, p->ai_socktype,
                                 p->ai_protocol)) == -1) {
                perror("server: socket");
                continue;
            }

            if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes,
                           sizeof(int)) == -1) {
                perror("setsockopt");
                exit(1);
            }

            //If we are here, we have found a socket to bind to.
            /* Give the socket FD (socket num?) the local address ADDR (which is LEN bytes long*/
            if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
                close(sockfd);
                perror("server: bind");
                continue;
            }

            break;
        }

        /* Free `addrinfo' structure AI including associated storage.  */
        freeaddrinfo(servinfo); // all done with this structure

        //p is the serverinfo.
        if (p == NULL) {
            fprintf(stderr, "server: failed to bind\n");
            exit(1);
        }

        //Tell socket to listen for incoming for incoming connections. sockfd.listen() think of it that way.
        if (listen(sockfd, BACKLOG) == -1) {
            perror("listen");
            exit(1);
        }

        printf("server: waiting for connections...\n");
    }
}
PhysicalLayer::~PhysicalLayer()
{

}

void PhysicalLayer::WaitForConnection()
{
    char s[INET6_ADDRSTRLEN];  //Create a char array of size 46. https://stackoverflow.com/questions/39443413/why-is-inet6-addrstrlen-defined-as-46-in-c

    struct sockaddr_storage their_addr; // connector's address information
    socklen_t sin_size;
    sin_size = sizeof their_addr;
    new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
    if (new_fd == -1) {
        perror("accept");
    }

    inet_ntop(their_addr.ss_family,
              get_in_addr((struct sockaddr *)&their_addr),
              s, sizeof s);
    printf("server: got connection from %s\n", s);

    //We are set up and listening in on the client.
}

string PhysicalLayer::ReadValues()
{
    if (!connectionEstablished)
    {
        WaitForConnection();//Call one time.
        connectionEstablished = true;
    }
    unsigned char buf[MAXDATASIZE + 1];//Add 1 since the last char must be a null char.
    int read_size;
    //Receive a message from client
    while( (read_size = recv(new_fd , buf , MAXDATASIZE + 1 , 0)) > 0 )
    {
        buf[read_size] = '\0'; //Clear last character of buf
        wcout << buf << endl;
        for (int i = 0; i < MAXDATASIZE + 1; i++)
        {
            if (buf[i] != '\0')
                entireEncodedFile += buf[i];
            else
                break;//We are done reading the incoming values.
        }
        //Instead of printing to the console, return all incoming values to the data link layer so that they can be decoded in the physical layer..
    }

    //Return to the data link layer with all of the encoded data.

    if(read_size == 0)
    {
        return entireEncodedFile;//We are done receiving transmissions.
//        puts("Client disconnected");
//        fflush(stdout);
    }
    else if(read_size == -1)
    {
        perror("recv failed");
    }
}

//Convert all of the chars to 1's and 0's.
void PhysicalLayer::Encode(unsigned char* frames, int allCharsInFrame, int bitToFlip)
{
    //datafield contains: syn, ctrl, data (up to 128 data chars) and syn.
    int parityToFlip = 0;
    unsigned char *completeTransmissionFrame = new unsigned char [MAXDATASIZE + 1];
    int locTransFrame = 0;
    int keepTrackOfEveryChar = 0;
    for (int loc = 0; loc < allCharsInFrame; loc++)
    {
        keepTrackOfEveryChar++;
        unsigned char theChar = frames[loc];
        //ASCII of 0 is 0110000
        //Stored in a byte: 00001100
        //Or with parity to store value.
        int parityCount = 0;
        int value;
        unsigned char character;
        for (int pos = 0; pos < 7; ++pos)//7 times
        {
            //if (theChar & '\x80') throw invalid byte exception.
            value = (int) (theChar >> pos) & 1;
            if (loc * 8 + (pos + 1) == bitToFlip)
            {
                //Once we've hit the bit we want to flip, change it from a 0 to a 1 or vice versa.
                //This will only run one time.
                if (value == 0)
                    value = 1;
                else
                    value = 0;
            }

            if (value == 1)
                character = (unsigned char) '\x31';
            else character = (unsigned char) '\x30';

            //Instead of writing to a file, place data in array until we have 1048 bytes.
            completeTransmissionFrame[locTransFrame] = character;
            locTransFrame++;

            //If we are at the bit we want to flip, then we don't want to correct the parity, otherwise we
            //will be changing two bits (i.e. the one we want to flip and the parity bit, which won't result in an error.)
            if (loc * 8 + (pos + 1) != bitToFlip)
            {
                if (value == 1)
                    parityCount++;
            }

            parityToFlip = pos + 1;
        }//End of adding parity to one char.

        //We've printed the 1's and 0's for the characters, now we have to print the parity.
        //Check to make sure that the bit to flip is not the parity.
        //Add 1 to the parityToFlip value because it previously held the last char that was printed.
        if (loc * 8 + (parityToFlip + 1) == bitToFlip)
            parityCount++;//If the bit we are flipping is a parity bit, simply add 1.

        //Make this odd parity.
        if (parityCount % 2 == 0)
            character = '\x31';
        else
            character = '\x30';

        //We have placed the seven bits of the data char in the frame, now add the parity.
        completeTransmissionFrame[locTransFrame] = character;
        locTransFrame++;

        //This will only occur once a parity bit has been placed in the completeTransmissionFrame.
        if (locTransFrame == MAXDATASIZE)
        {
            //We have filled an entire transmission frame, send it.
            locTransFrame = 0; //Reset to zero since we will be starting a new transmission frame.
            unsigned char *charArray = new unsigned char[MAXDATASIZE + 1];
            charArray[MAXDATASIZE + 1] = '\0';

            int charNum = 0;
            while((charNum != (MAXDATASIZE + 1)) && (completeTransmissionFrame[charNum] != '\0'))
            {
                charArray[charNum] = completeTransmissionFrame[charNum];
                charNum++;
            }
            if (send(sockfd, charArray, charNum, 0) == -1)
                perror("Sending failed.");

            //Instead of writing to a file, send data through socket.
        }
    }
    //We still have a left over frame to send.
    if (locTransFrame < MAXDATASIZE)
    {
        //We have exited the for loop, now we have to send the partial frame.
        //We have filled the partial frame transmission frame, send it.
        unsigned char *charArray = new unsigned char[MAXDATASIZE + 1];
        charArray[MAXDATASIZE + 1] = '\0';

        int charNum = 0;
        while((charNum != (MAXDATASIZE + 1)) && (charNum < locTransFrame)) //completeTransmissionFrame[charNum] != '\0'
        {
            charArray[charNum] = completeTransmissionFrame[charNum];
            charNum++;
        }
        if (send(sockfd, charArray, charNum, 0) == -1)
            perror("Sending failed.");
        //Close the socket once all of the transmission have been sent.
        close(sockfd);
    }
}

//Convert the 1's and 0's to chars.
unsigned char* PhysicalLayer::Decode(string allDataFromTransmission)
{
    int charLength = allDataFromTransmission.length() / 8;
    unsigned char *bytes = new unsigned char[allDataFromTransmission.length()];
    int loc = 0;
    //For every 0 or 1 in the string, put that in the bytes array.
    for (int i = 0; i < allDataFromTransmission.length(); i++)
    {
        bytes[i] = allDataFromTransmission.at(i);
    }
    //Now that we have read in all the 1's and 0's, do the parity check and construct the chars.
    int parityValue;
    int onesCount;
    unsigned char charToCreate;
    unsigned char *characters = new unsigned char[charLength];

    for (int count = 1; count <= charLength; count++)
    {
        //Reset our char that we are creating and the ones count.
        charToCreate = 0x0;
        onesCount = 0;
        charLocation++;//Keep track of the char we are at.
        parityValue = bytes[(count * 8) - 1];//This is the last bit of the char.
        for (int position = count * 8 - 2, forward = 6; position >= (count - 1) * 8; position--, forward--)
        {
            unsigned char tempCharacter = bytes[position];
            if (tempCharacter == 49)
            {
                onesCount++;
                charToCreate |= 1 << forward;
            }
        }

        int onesModded = onesCount % 2;
        string message;
        //We had an odd number of 1's.
        if (parityValue == 48)
        {
            //This is an error.
            if (onesModded == 0)
                throw 2;

            else
                characters[charLocation - 1] = charToCreate;
        }
        //We had an even number of 1's.
        else
        {
            if (onesModded == 0)
                characters[charLocation - 1] = charToCreate;
            else
                throw 2;

        }
    }
    return characters;
}

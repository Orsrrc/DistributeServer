#ifndef __CONSENSUS__H_
#define __CONSENSUS__H_



#include <unordered_map>
#include "Common.hpp"

// Define message types
enum class MessageType { PRE_PREPARE, PREPARE, COMMIT };

// Define message structure
struct Message {
    int view;
    int sequence_number;
    MessageType type;
    // Add more fields as needed
};

// Define replica state
struct ReplicaState {
    int view;
    int last_executed;
    // Add more fields as needed
};


// Define PBFT class
class PBFT {

public:
    PBFT(int num_replicas) : num_replicas(num_replicas) {
        // Initialize replica states
        for (int i = 0; i < num_replicas; ++i) {
            replica_states[i] = {0, -1}; // Initialize view and last_executed
        }
    }

    // Handle incoming message
    void handle_message(Message msg) {
        switch (msg.type) {
            case MessageType::PRE_PREPARE:
                // Process PRE-PREPARE message
                break;
            case MessageType::PREPARE:
                // Process PREPARE message
                break;
            case MessageType::COMMIT:
                // Process COMMIT message
                break;
            default:
                std::cerr << "Unknown message type\n";
                break;
        }
    }

    // Main execution logic
    void execute() {
        // Main execution loop
        while (true) {
            // Receive message
            Message msg;
            // Example: Receive message from network

            // Process message
            handle_message(msg);

            // Check for conditions to send messages
            // Example: if (condition) send_pre_prepare();
        }
    }

    // Example: Send PRE-PREPARE message
    void send_pre_prepare() {
        // Construct PRE-PREPARE message
        Message msg;
        msg.view = replica_states[0].view;
        msg.sequence_number = replica_states[0].last_executed + 1;
        msg.type = MessageType::PRE_PREPARE;

        // Example: Broadcast message over network
    }


private:
    int num_replicas;
    std::unordered_map<int, ReplicaState> replica_states;

};


#endif //__CONSENSUS__H_

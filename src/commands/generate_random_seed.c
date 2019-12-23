#include <ulfius.h>

struct generate_random_seed_validation_result {
    bool successful;
    crypto_core_json_validation_error_t validation_error;
    json_t *key_ptr;
};

struct generate_random_seed_validation_result generate_random_seed_validate_json(json_t *json_ptr){
    struct generate_random_seed_validation_result result = {.successful = false};

    json_t *key_json_ptr = json_object_get(json_ptr, "key");
    if (json_is_null(key_json_ptr) || key_json_ptr == NULL) {
        result.validation_error = ERROR_KEY_MISSING;

        return result;
    }

    if (trunk_transaction_json_ptr->type != JSON_INTEGER) {
        result.validation_error = KEY_NOT_NUMBER_MESSAGE;

        return result;
    }

    result.successful = true;
    result.key_ptr = key_json_ptr;

    return result;
}

void generate_random_seed_handle_request(json_t *json_ptr, struct _u_response *response) {
    struct generate_random_seed_validation_result validation_result = generate_random_seed_validate_json(json_ptr);

    if (validation_result.successful) {
        //Todo: Implement UART and response
        ulfius_set_string_body_response(response, 200, "generateRandomSeed");
    } else {
        send_error_message(response, validation_result.validation_error);
    }
}
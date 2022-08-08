//
//  try.cpp
//  Test_Drive_1
//

#include <iostream>
#include <MicrosoftCognitiveServicesSpeech/speechapi_cxx.h>

using namespace std;
using namespace Microsoft::CognitiveServices::Speech;
using namespace Microsoft::CognitiveServices::Speech::Intent;

void recognizeIntent()
{
    // </skeleton_1>
    // Creates an instance of a speech config with specified subscription key
    // and service region. Note that in contrast to other services supported by
    // the Cognitive Services Speech SDK, the Language Understanding service
    // requires a specific subscription key from https://www.luis.ai/.
    // The Language Understanding service calls the required key 'endpoint key'.
    // Once you've obtained it, replace with below with your own Language Understanding subscription key
    // and service region (e.g., "westus").
    // The default recognition language is "en-us".
    // <create_speech_configuration>
    auto config = SpeechConfig::FromSubscription("320f2ba488a54a21900494155eb889f8", "eastus");

    // </create_speech_configuration>

    // <create_intent_recognizer>
    // Creates an intent recognizer using microphone as audio input.
    auto recognizer = IntentRecognizer::FromConfig(config);
    // </create_intent_recognizer>

    // <add_intents>
    // Creates a Language Understanding model using the app id, and adds specific intents from your model
    auto model = LanguageUnderstandingModel::FromAppId("ffc48ea7-337d-43dc-85a3-c3dce348764d");
    //recognizer->AddIntent(model, "YourLanguageUnderstandingIntentName3", "any-IntentId-here");
    // </add_intents>
    
//    recognizer->AddEntity(model,)

    // To add all of the possible intents from a LUIS model to the recognizer, uncomment the line below:
     recognizer->AddAllIntents(model);
    

    // <recognize_intent>
    cout << "Say something...\n" << std::endl;

    // Starts intent recognition, and returns after a single utterance is recognized. The end of a
    // single utterance is determined by listening for silence at the end or until a maximum of 15
    // seconds of audio is processed.  The task returns the recognition text as result.
    // Note: Since RecognizeOnceAsync() returns only a single utterance, it is suitable only for single
    // shot recognition like command or query.
    // For long-running multi-utterance recognition, use StartContinuousRecognitionAsync() instead.
    auto result = recognizer->RecognizeOnceAsync().get();
    // </recognize_intent>

    // <print_results>
    // Checks result.
    if (result->Reason == ResultReason::RecognizedIntent)
    {
        cout << "RECOGNIZED: Text=" << result->Text << std::endl;
        cout << "  Intent Id: " << result->IntentId << std::endl;
        cout << "  Intent Service JSON: " << result->Properties.GetProperty(PropertyId::LanguageUnderstandingServiceResponse_JsonResult) << std::endl;
    }
    else if (result->Reason == ResultReason::RecognizedSpeech)
    {
        cout << "RECOGNIZED: Text=" << result->Text << " (intent could not be recognized)" << std::endl;
    }
    else if (result->Reason == ResultReason::NoMatch)
    {
        cout << "NOMATCH: Speech could not be recognized." << std::endl;
    }
    else if (result->Reason == ResultReason::Canceled)
    {
        auto cancellation = CancellationDetails::FromResult(result);
        cout << "CANCELED: Reason=" << (int)cancellation->Reason << std::endl;

        if (cancellation->Reason == CancellationReason::Error)
        {
            cout << "CANCELED: ErrorCode=" << (int)cancellation->ErrorCode << std::endl;
            cout << "CANCELED: ErrorDetails=" << cancellation->ErrorDetails << std::endl;
            cout << "CANCELED: Did you update the subscription info?" << std::endl;
        }
    }
    // </print_results>
    // <skeleton_2>
}

int main(int argc, char **argv)
{
    try
    {
        recognizeIntent();
    }
    catch (exception e)
    {
        cout << e.what();
    }
    cout << "Please press a key to continue.\n";
    cin.get();
    return 0;
}
